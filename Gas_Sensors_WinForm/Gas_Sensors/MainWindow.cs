using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO.Ports;
using System.Threading;

namespace Gas_Sensors
{
    public partial class MainWindow : Form
    {

        #region 公共变量声明
        SerialPort mySerialPort = new SerialPort();

        //系统时间定时器
        System.Windows.Forms.Timer timer1 = new System.Windows.Forms.Timer();
        //自动发送定时器
        System.Windows.Forms.Timer timer2 = new System.Windows.Forms.Timer();

        public bool ckHexState;
        public static byte[] bufData = new byte[1024];
        private delegate void UpdateStatusDelegate();
        #endregion

        public MainWindow()
        {
            InitializeComponent();
        }

        #region 主窗体加载函数
        private void MainWindow_Load(object sender, EventArgs e)
        {
            #region//串口设置初始化
            //串口cbComName.Text
            string[] portsName = SerialPort.GetPortNames();
            Array.Sort(portsName);
            cbPortName.DataSource = portsName;
            cbPortName.Text = Convert.ToString(cbPortName.Items[0]);
            //波特率cbBaudRate.Text
            int[] baudRateData = { 4800, 9600, 19200, 38400, 43000, 56000 };
            cbBaudRate.DataSource = baudRateData;
            cbBaudRate.Text = Convert.ToString(cbBaudRate.Items[1]);
            //检验位cbParity.Text
            string[] parityBit = { "无", "奇校验", "偶校验" };
            cbParity.DataSource = parityBit;
            cbParity.Text = Convert.ToString(cbParity.Items[0]);
            //数据位cbDataBits.Text
            int[] dataBits = { 6, 7, 8 };
            cbDataBits.DataSource = dataBits;
            cbDataBits.Text = Convert.ToString(cbDataBits.Items[2]);
            //停止位cbStopBits.Text
            int[] stopBits = { 1, 2 };
            cbStopBits.DataSource = stopBits;
            cbStopBits.Text = Convert.ToString(cbStopBits.Items[0]);
            #endregion

            mySerialPort.DataReceived += new SerialDataReceivedEventHandler(this.mySerialPort_DataReceived);
            mySerialPort.Encoding = System.Text.Encoding.GetEncoding("GB2312");
            ckHexState = (bool)ck16View.Checked;

            this.timer1.Interval = 1000;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            this.timer1.Start();

            timer2.Tick += new EventHandler(timer2_Tick);
        }
        #endregion 

        #region 打开串口点击事件
        private void btnOpenCom_Click(object sender, EventArgs e)
        {

            if (mySerialPort.IsOpen)
            {
                mySerialPort.Close();
                cbBaudRate.Enabled = true;
                cbDataBits.Enabled = true;
                cbParity.Enabled = true;
                cbPortName.Enabled = true;
                cbStopBits.Enabled = true;
                btnOpenCom.Text = "打开串口";
                pbComState.Image = Gas_Sensors.Properties.Resources.Off;
            }
            else
            {
                mySerialPort.PortName = cbPortName.Text;
                mySerialPort.BaudRate = Convert.ToInt32(cbBaudRate.Text);
                switch (Convert.ToString(cbParity.Text))
                {
                    case "无":
                        mySerialPort.Parity = Parity.None;
                        break;
                    case "奇校验":
                        mySerialPort.Parity = Parity.Odd;
                        break;
                    case "偶校验":
                        mySerialPort.Parity = Parity.Even;
                        break;
                }
                switch (Convert.ToInt32(cbStopBits.Text))
                {
                    case 0:
                        mySerialPort.StopBits = StopBits.None;
                        break;
                    case 1:
                        mySerialPort.StopBits = StopBits.One;
                        break;
                    case 2:
                        mySerialPort.StopBits = StopBits.Two;
                        break;
                }
                try
                {
                    mySerialPort.Open();
                }
                catch
                {
                    //tbComState.Text = cbPortName.Text + "串口被占用！";
                    MessageBox.Show("串口被占用！");
                    return;
                }
                cbBaudRate.Enabled = false;
                cbDataBits.Enabled = false;
                cbParity.Enabled = false;
                cbPortName.Enabled = false;
                cbStopBits.Enabled = false;
                btnOpenCom.Text = "关闭串口";
               // tbComState.Text = cbPortName.Text + "," + cbBaudRate.Text + "," +
                //    cbParity.Text + "," + cbDataBits.Text + "," + cbStopBits.Text;
                pbComState.Image = Gas_Sensors.Properties.Resources.On;
            }
        }
        #endregion

        #region 定时器1 Tick事件
        private void timer1_Tick(object sender, EventArgs e)
        {
            lbSystemTime.Text = DateTime.Now.ToString();
        }
        #endregion

        #region 定时器2 Tick事件
        private void timer2_Tick(object sender, EventArgs e)
        {
            if (mySerialPort.IsOpen)
            {
                btSend_Event(tbSend.Text, (bool)ck16Send.Checked);
            }
        }
        #endregion

        #region Delegate Functions

        public delegate void GUIStatus(string paramString);
        public void DoGUIStatusReceivedData(string paramString)
        {
            if (this.InvokeRequired)
            {
                GUIStatus delegateMethod = new GUIStatus(this.DoGUIStatusReceivedData);
                this.Invoke(delegateMethod, new object[] { paramString });
            }
            else
            {
                this.tbReceive.AppendText(paramString);
            }
        }

        #endregion

        #region 串口数据接收
        private void mySerialPort_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            string abc="", abc1;

            Thread.Sleep(200);

            int n = mySerialPort.BytesToRead;
            byte[] buf = new byte[n];
            mySerialPort.Read(buf, 0, n);
           
           
            if (buf.Length > 0)
            {
                if (ckHexState == true)
                {
                    abc = ByteArrayToHexString(buf);
                    string hexStringView = "";
                    for (int i = 0; i < abc.Length; i += 2)
                    {
                        hexStringView += abc.Substring(i, 2) + " ";
                    }
                    abc = hexStringView;
                    abc1 = abc.Replace(" ", "");
                    if (abc1.Substring(abc1.Length - 2, 2) == "0D")
                    {
                        abc = abc + "\n";
                    }

                }
                else
                {
                    abc = System.Text.Encoding.Default.GetString(buf);
                }


                if (buf[0] == 0x41 && buf.Length >= 17)
                {
                    bufData = buf;
                    this.BeginInvoke(new UpdateStatusDelegate(UpdateGasData), new object[] { });
                }
            }

            DoGUIStatusReceivedData(abc);
        }
        #endregion

        #region 更新窗体气体传感器数据
        private void UpdateGasData()
        {
            txtPM25Value.Text = (bufData[1] * 256 + bufData[2]).ToString();
            txtPM10Value.Text = (bufData[3] * 256 + bufData[4]).ToString();
            txtTVOCValue.Text = (bufData[5] * 256 + bufData[6]).ToString();
            txtCH2OValue.Text = (bufData[7] * 256 + bufData[8]).ToString();
            txtCO2Value.Text = (bufData[9] * 256 + bufData[10]).ToString();
            txtCOValue.Text = (bufData[11] * 256 + bufData[12]).ToString();
            txtTempValue.Text = ((bufData[13] * 256 + bufData[14])/10.0).ToString();
            txtHumiValue.Text = ((bufData[15] * 256 + bufData[16])/10.0).ToString();
        }
        #endregion

        #region 字节数据转16进制
        public string ByteArrayToHexString(byte[] data)
        {
            StringBuilder sb = new StringBuilder(data.Length * 3);
            foreach (byte b in data)
                sb.Append(Convert.ToString(b, 16).PadLeft(2, '0'));
            return sb.ToString().ToUpper();
        }
        #endregion

        #region 16进制转字节数组
        public byte[] HexStringToByteArray(string s)
        {
            //s=s.ToUpper();
            s = s.Replace(" ", "");
            if (s.Length % 2 != 0)
            {
                s = s.Substring(0, s.Length - 1) + "0" + s.Substring(s.Length - 1);
            }
            byte[] buffer = new byte[s.Length / 2];


            try
            {
                for (int i = 0; i < s.Length; i += 2)
                    buffer[i / 2] = (byte)Convert.ToByte(s.Substring(i, 2), 16);
                return buffer;
            }
            catch
            {
                string errorString = "E4";
                byte[] errorData = new byte[errorString.Length / 2];
                errorData[0] = (byte)Convert.ToByte(errorString, 16);
                return errorData;
            }
        }
        #endregion

        #region 16进制显示
        private void ck16View_CheckedChanged(object sender, EventArgs e)
        {
            ckHexState = (bool)ck16View.Checked;
        }
        #endregion

        #region 发送按钮点击事件
        private void btSend_Click(object sender, EventArgs e)
        {
            btSend_Event(tbSend.Text, (bool)ck16Send.Checked);
        }
        #endregion

        #region 串口数据发送
        private void btSend_Event(string strSend, bool hexState)
        {
            if (mySerialPort.IsOpen)
            {
                if (hexState == false)
                {
                    //if (ckAdvantechCmd.IsChecked == true) { strSend = strSend.ToUpper(); }
                    byte[] sendData = System.Text.Encoding.Default.GetBytes(strSend);
                    mySerialPort.Write(sendData, 0, sendData.Length);
                   
                }
                else
                {
                    byte[] sendHexData = HexStringToByteArray(strSend);
                    mySerialPort.Write(sendHexData, 0, sendHexData.Length);
                }
            }
            else
            {
                MessageBox.Show("串口没有打开，请检查！");
            }
        }
        #endregion

        #region 清空接收区
        private void btnCleartbRece_Click(object sender, EventArgs e)
        {
            tbReceive.Text = "";
        }
        #endregion

        #region 清空发送区
        private void btnCleartbSend_Click(object sender, EventArgs e)
        {
            tbSend.Text = "";
        }
        #endregion

        #region 自动发送
        private void ckAutoSend_CheckedChanged(object sender, EventArgs e)
        {
            if (mySerialPort.IsOpen == false)
            {
                MessageBox.Show("串口未开！");
                ckAutoSend.Checked = false;
                return;
            }
            if (ckAutoSend.Checked == true)
            {
                timer2.Interval = Convert.ToInt32(tbIntervalTime.Text);
                if (Convert.ToDouble(tbIntervalTime.Text) == 0)
                {
                    return;
                }
                else
                {
                    timer2.Start();
                }
            }
            else
            {
                timer2.Stop();
            }
        }
        #endregion

        #region 更新自动发送周期
        private void tbIntervalTime_TextChanged(object sender, EventArgs e)
        {
            if (ckAutoSend.Checked == true)
            {
                timer2.Interval = Convert.ToInt32(tbIntervalTime.Text);
            }
        }
        #endregion
    }
}
