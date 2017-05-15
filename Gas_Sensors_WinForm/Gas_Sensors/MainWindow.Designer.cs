namespace Gas_Sensors
{
    partial class MainWindow
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainWindow));
            this.lbPortName = new System.Windows.Forms.Label();
            this.cbPortName = new System.Windows.Forms.ComboBox();
            this.cbBaudRate = new System.Windows.Forms.ComboBox();
            this.lbBaundRate = new System.Windows.Forms.Label();
            this.cbParity = new System.Windows.Forms.ComboBox();
            this.lbParity = new System.Windows.Forms.Label();
            this.cbDataBits = new System.Windows.Forms.ComboBox();
            this.lbDataBits = new System.Windows.Forms.Label();
            this.cbStopBits = new System.Windows.Forms.ComboBox();
            this.lbStopBits = new System.Windows.Forms.Label();
            this.btnOpenCom = new System.Windows.Forms.Button();
            this.pbComState = new System.Windows.Forms.PictureBox();
            this.tbReceive = new System.Windows.Forms.TextBox();
            this.tbSend = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.txtHumiValue = new System.Windows.Forms.TextBox();
            this.label8 = new System.Windows.Forms.Label();
            this.txtTempValue = new System.Windows.Forms.TextBox();
            this.label9 = new System.Windows.Forms.Label();
            this.txtCOValue = new System.Windows.Forms.TextBox();
            this.label10 = new System.Windows.Forms.Label();
            this.txtCO2Value = new System.Windows.Forms.TextBox();
            this.label11 = new System.Windows.Forms.Label();
            this.txtCH2OValue = new System.Windows.Forms.TextBox();
            this.label7 = new System.Windows.Forms.Label();
            this.txtTVOCValue = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.txtPM10Value = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.txtPM25Value = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.label3 = new System.Windows.Forms.Label();
            this.lbSystemTime = new System.Windows.Forms.Label();
            this.ck16View = new System.Windows.Forms.CheckBox();
            this.ck16Send = new System.Windows.Forms.CheckBox();
            this.btSend = new System.Windows.Forms.Button();
            this.btnCleartbRece = new System.Windows.Forms.Button();
            this.btnCleartbSend = new System.Windows.Forms.Button();
            this.ckAutoSend = new System.Windows.Forms.CheckBox();
            this.label12 = new System.Windows.Forms.Label();
            this.tbIntervalTime = new System.Windows.Forms.TextBox();
            this.label13 = new System.Windows.Forms.Label();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            ((System.ComponentModel.ISupportInitialize)(this.pbComState)).BeginInit();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // lbPortName
            // 
            this.lbPortName.AutoSize = true;
            this.lbPortName.Location = new System.Drawing.Point(45, 40);
            this.lbPortName.Name = "lbPortName";
            this.lbPortName.Size = new System.Drawing.Size(53, 12);
            this.lbPortName.TabIndex = 0;
            this.lbPortName.Text = "串口号：";
            // 
            // cbPortName
            // 
            this.cbPortName.FormattingEnabled = true;
            this.cbPortName.Location = new System.Drawing.Point(95, 37);
            this.cbPortName.Name = "cbPortName";
            this.cbPortName.Size = new System.Drawing.Size(81, 20);
            this.cbPortName.TabIndex = 1;
            // 
            // cbBaudRate
            // 
            this.cbBaudRate.FormattingEnabled = true;
            this.cbBaudRate.Location = new System.Drawing.Point(95, 63);
            this.cbBaudRate.Name = "cbBaudRate";
            this.cbBaudRate.Size = new System.Drawing.Size(81, 20);
            this.cbBaudRate.TabIndex = 3;
            // 
            // lbBaundRate
            // 
            this.lbBaundRate.AutoSize = true;
            this.lbBaundRate.Location = new System.Drawing.Point(45, 66);
            this.lbBaundRate.Name = "lbBaundRate";
            this.lbBaundRate.Size = new System.Drawing.Size(53, 12);
            this.lbBaundRate.TabIndex = 2;
            this.lbBaundRate.Text = "波特率：";
            // 
            // cbParity
            // 
            this.cbParity.FormattingEnabled = true;
            this.cbParity.Location = new System.Drawing.Point(95, 89);
            this.cbParity.Name = "cbParity";
            this.cbParity.Size = new System.Drawing.Size(81, 20);
            this.cbParity.TabIndex = 5;
            // 
            // lbParity
            // 
            this.lbParity.AutoSize = true;
            this.lbParity.Location = new System.Drawing.Point(45, 92);
            this.lbParity.Name = "lbParity";
            this.lbParity.Size = new System.Drawing.Size(53, 12);
            this.lbParity.TabIndex = 4;
            this.lbParity.Text = "校验位：";
            // 
            // cbDataBits
            // 
            this.cbDataBits.FormattingEnabled = true;
            this.cbDataBits.Location = new System.Drawing.Point(95, 115);
            this.cbDataBits.Name = "cbDataBits";
            this.cbDataBits.Size = new System.Drawing.Size(81, 20);
            this.cbDataBits.TabIndex = 7;
            // 
            // lbDataBits
            // 
            this.lbDataBits.AutoSize = true;
            this.lbDataBits.Location = new System.Drawing.Point(45, 118);
            this.lbDataBits.Name = "lbDataBits";
            this.lbDataBits.Size = new System.Drawing.Size(53, 12);
            this.lbDataBits.TabIndex = 6;
            this.lbDataBits.Text = "数据位：";
            // 
            // cbStopBits
            // 
            this.cbStopBits.FormattingEnabled = true;
            this.cbStopBits.Location = new System.Drawing.Point(95, 141);
            this.cbStopBits.Name = "cbStopBits";
            this.cbStopBits.Size = new System.Drawing.Size(81, 20);
            this.cbStopBits.TabIndex = 9;
            // 
            // lbStopBits
            // 
            this.lbStopBits.AutoSize = true;
            this.lbStopBits.Location = new System.Drawing.Point(45, 144);
            this.lbStopBits.Name = "lbStopBits";
            this.lbStopBits.Size = new System.Drawing.Size(53, 12);
            this.lbStopBits.TabIndex = 8;
            this.lbStopBits.Text = "停止位：";
            // 
            // btnOpenCom
            // 
            this.btnOpenCom.Location = new System.Drawing.Point(95, 168);
            this.btnOpenCom.Name = "btnOpenCom";
            this.btnOpenCom.Size = new System.Drawing.Size(81, 27);
            this.btnOpenCom.TabIndex = 10;
            this.btnOpenCom.Text = "打开串口";
            this.btnOpenCom.UseVisualStyleBackColor = true;
            this.btnOpenCom.Click += new System.EventHandler(this.btnOpenCom_Click);
            // 
            // pbComState
            // 
            this.pbComState.Image = global::Gas_Sensors.Properties.Resources.Off;
            this.pbComState.Location = new System.Drawing.Point(47, 168);
            this.pbComState.Name = "pbComState";
            this.pbComState.Size = new System.Drawing.Size(28, 27);
            this.pbComState.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pbComState.TabIndex = 11;
            this.pbComState.TabStop = false;
            // 
            // tbReceive
            // 
            this.tbReceive.Location = new System.Drawing.Point(20, 240);
            this.tbReceive.Multiline = true;
            this.tbReceive.Name = "tbReceive";
            this.tbReceive.Size = new System.Drawing.Size(585, 134);
            this.tbReceive.TabIndex = 12;
            // 
            // tbSend
            // 
            this.tbSend.Location = new System.Drawing.Point(20, 408);
            this.tbSend.Multiline = true;
            this.tbSend.Name = "tbSend";
            this.tbSend.Size = new System.Drawing.Size(585, 99);
            this.tbSend.TabIndex = 13;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(23, 222);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(65, 12);
            this.label1.TabIndex = 14;
            this.label1.Text = "接收数据：";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(23, 390);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(65, 12);
            this.label2.TabIndex = 15;
            this.label2.Text = "发送数据：";
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.txtHumiValue);
            this.groupBox1.Controls.Add(this.label8);
            this.groupBox1.Controls.Add(this.txtTempValue);
            this.groupBox1.Controls.Add(this.label9);
            this.groupBox1.Controls.Add(this.txtCOValue);
            this.groupBox1.Controls.Add(this.label10);
            this.groupBox1.Controls.Add(this.txtCO2Value);
            this.groupBox1.Controls.Add(this.label11);
            this.groupBox1.Controls.Add(this.txtCH2OValue);
            this.groupBox1.Controls.Add(this.label7);
            this.groupBox1.Controls.Add(this.txtTVOCValue);
            this.groupBox1.Controls.Add(this.label6);
            this.groupBox1.Controls.Add(this.txtPM10Value);
            this.groupBox1.Controls.Add(this.label5);
            this.groupBox1.Controls.Add(this.txtPM25Value);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.groupBox1.Location = new System.Drawing.Point(207, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(550, 196);
            this.groupBox1.TabIndex = 16;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Gas Sensor Value:";
            // 
            // txtHumiValue
            // 
            this.txtHumiValue.Location = new System.Drawing.Point(363, 146);
            this.txtHumiValue.Name = "txtHumiValue";
            this.txtHumiValue.ReadOnly = true;
            this.txtHumiValue.Size = new System.Drawing.Size(100, 26);
            this.txtHumiValue.TabIndex = 15;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(299, 150);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(51, 16);
            this.label8.TabIndex = 14;
            this.label8.Text = "湿度:";
            // 
            // txtTempValue
            // 
            this.txtTempValue.Location = new System.Drawing.Point(363, 113);
            this.txtTempValue.Name = "txtTempValue";
            this.txtTempValue.ReadOnly = true;
            this.txtTempValue.Size = new System.Drawing.Size(100, 26);
            this.txtTempValue.TabIndex = 13;
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(299, 117);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(51, 16);
            this.label9.TabIndex = 12;
            this.label9.Text = "温度:";
            // 
            // txtCOValue
            // 
            this.txtCOValue.Location = new System.Drawing.Point(363, 80);
            this.txtCOValue.Name = "txtCOValue";
            this.txtCOValue.ReadOnly = true;
            this.txtCOValue.Size = new System.Drawing.Size(100, 26);
            this.txtCOValue.TabIndex = 11;
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(299, 84);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(35, 16);
            this.label10.TabIndex = 10;
            this.label10.Text = "CO:";
            // 
            // txtCO2Value
            // 
            this.txtCO2Value.Location = new System.Drawing.Point(363, 47);
            this.txtCO2Value.Name = "txtCO2Value";
            this.txtCO2Value.ReadOnly = true;
            this.txtCO2Value.Size = new System.Drawing.Size(100, 26);
            this.txtCO2Value.TabIndex = 9;
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(299, 51);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(44, 16);
            this.label11.TabIndex = 8;
            this.label11.Text = "CO2:";
            // 
            // txtCH2OValue
            // 
            this.txtCH2OValue.Location = new System.Drawing.Point(162, 145);
            this.txtCH2OValue.Name = "txtCH2OValue";
            this.txtCH2OValue.ReadOnly = true;
            this.txtCH2OValue.Size = new System.Drawing.Size(100, 26);
            this.txtCH2OValue.TabIndex = 7;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(98, 149);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(51, 16);
            this.label7.TabIndex = 6;
            this.label7.Text = "甲醛:";
            // 
            // txtTVOCValue
            // 
            this.txtTVOCValue.Location = new System.Drawing.Point(162, 112);
            this.txtTVOCValue.Name = "txtTVOCValue";
            this.txtTVOCValue.ReadOnly = true;
            this.txtTVOCValue.Size = new System.Drawing.Size(100, 26);
            this.txtTVOCValue.TabIndex = 5;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(98, 116);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(53, 16);
            this.label6.TabIndex = 4;
            this.label6.Text = "TVOC:";
            // 
            // txtPM10Value
            // 
            this.txtPM10Value.Location = new System.Drawing.Point(162, 79);
            this.txtPM10Value.Name = "txtPM10Value";
            this.txtPM10Value.ReadOnly = true;
            this.txtPM10Value.Size = new System.Drawing.Size(100, 26);
            this.txtPM10Value.TabIndex = 3;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(98, 83);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(53, 16);
            this.label5.TabIndex = 2;
            this.label5.Text = "PM10:";
            // 
            // txtPM25Value
            // 
            this.txtPM25Value.Location = new System.Drawing.Point(162, 46);
            this.txtPM25Value.Name = "txtPM25Value";
            this.txtPM25Value.ReadOnly = true;
            this.txtPM25Value.Size = new System.Drawing.Size(100, 26);
            this.txtPM25Value.TabIndex = 1;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(98, 50);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(62, 16);
            this.label4.TabIndex = 0;
            this.label4.Text = "PM2.5:";
            // 
            // groupBox2
            // 
            this.groupBox2.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.groupBox2.Location = new System.Drawing.Point(20, 12);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(177, 196);
            this.groupBox2.TabIndex = 17;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Com Set:";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(583, 515);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(65, 12);
            this.label3.TabIndex = 18;
            this.label3.Text = "系统时间：";
            // 
            // lbSystemTime
            // 
            this.lbSystemTime.AutoSize = true;
            this.lbSystemTime.Location = new System.Drawing.Point(654, 515);
            this.lbSystemTime.Name = "lbSystemTime";
            this.lbSystemTime.Size = new System.Drawing.Size(0, 12);
            this.lbSystemTime.TabIndex = 19;
            // 
            // ck16View
            // 
            this.ck16View.AutoSize = true;
            this.ck16View.Location = new System.Drawing.Point(664, 284);
            this.ck16View.Name = "ck16View";
            this.ck16View.Size = new System.Drawing.Size(84, 16);
            this.ck16View.TabIndex = 20;
            this.ck16View.Text = "16进制显示";
            this.ck16View.UseVisualStyleBackColor = true;
            this.ck16View.CheckedChanged += new System.EventHandler(this.ck16View_CheckedChanged);
            // 
            // ck16Send
            // 
            this.ck16Send.AutoSize = true;
            this.ck16Send.Location = new System.Drawing.Point(620, 415);
            this.ck16Send.Name = "ck16Send";
            this.ck16Send.Size = new System.Drawing.Size(84, 16);
            this.ck16Send.TabIndex = 21;
            this.ck16Send.Text = "16进制发送";
            this.ck16Send.UseVisualStyleBackColor = true;
            // 
            // btSend
            // 
            this.btSend.Location = new System.Drawing.Point(620, 470);
            this.btSend.Name = "btSend";
            this.btSend.Size = new System.Drawing.Size(81, 27);
            this.btSend.TabIndex = 22;
            this.btSend.Text = "发    送";
            this.btSend.UseVisualStyleBackColor = true;
            this.btSend.Click += new System.EventHandler(this.btSend_Click);
            // 
            // btnCleartbRece
            // 
            this.btnCleartbRece.Location = new System.Drawing.Point(664, 306);
            this.btnCleartbRece.Name = "btnCleartbRece";
            this.btnCleartbRece.Size = new System.Drawing.Size(81, 27);
            this.btnCleartbRece.TabIndex = 23;
            this.btnCleartbRece.Text = "清空接收区";
            this.btnCleartbRece.UseVisualStyleBackColor = true;
            this.btnCleartbRece.Click += new System.EventHandler(this.btnCleartbRece_Click);
            // 
            // btnCleartbSend
            // 
            this.btnCleartbSend.Location = new System.Drawing.Point(620, 437);
            this.btnCleartbSend.Name = "btnCleartbSend";
            this.btnCleartbSend.Size = new System.Drawing.Size(81, 27);
            this.btnCleartbSend.TabIndex = 24;
            this.btnCleartbSend.Text = "清空发送区";
            this.btnCleartbSend.UseVisualStyleBackColor = true;
            this.btnCleartbSend.Click += new System.EventHandler(this.btnCleartbSend_Click);
            // 
            // ckAutoSend
            // 
            this.ckAutoSend.AutoSize = true;
            this.ckAutoSend.Location = new System.Drawing.Point(709, 415);
            this.ckAutoSend.Name = "ckAutoSend";
            this.ckAutoSend.Size = new System.Drawing.Size(72, 16);
            this.ckAutoSend.TabIndex = 25;
            this.ckAutoSend.Text = "自动发送";
            this.ckAutoSend.UseVisualStyleBackColor = true;
            this.ckAutoSend.CheckedChanged += new System.EventHandler(this.ckAutoSend_CheckedChanged);
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(709, 444);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(41, 12);
            this.label12.TabIndex = 26;
            this.label12.Text = "周期：";
            // 
            // tbIntervalTime
            // 
            this.tbIntervalTime.Location = new System.Drawing.Point(711, 474);
            this.tbIntervalTime.Name = "tbIntervalTime";
            this.tbIntervalTime.Size = new System.Drawing.Size(46, 21);
            this.tbIntervalTime.TabIndex = 27;
            this.tbIntervalTime.Text = "1000";
            this.tbIntervalTime.TextChanged += new System.EventHandler(this.tbIntervalTime_TextChanged);
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(762, 477);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(17, 12);
            this.label13.TabIndex = 28;
            this.label13.Text = "ms";
            // 
            // groupBox3
            // 
            this.groupBox3.Location = new System.Drawing.Point(620, 233);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(159, 141);
            this.groupBox3.TabIndex = 29;
            this.groupBox3.TabStop = false;
            // 
            // groupBox4
            // 
            this.groupBox4.Location = new System.Drawing.Point(611, 397);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(172, 110);
            this.groupBox4.TabIndex = 30;
            this.groupBox4.TabStop = false;
            // 
            // MainWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(791, 534);
            this.Controls.Add(this.label13);
            this.Controls.Add(this.tbIntervalTime);
            this.Controls.Add(this.label12);
            this.Controls.Add(this.ckAutoSend);
            this.Controls.Add(this.btnCleartbSend);
            this.Controls.Add(this.btnCleartbRece);
            this.Controls.Add(this.btSend);
            this.Controls.Add(this.ck16Send);
            this.Controls.Add(this.ck16View);
            this.Controls.Add(this.lbSystemTime);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.tbSend);
            this.Controls.Add(this.tbReceive);
            this.Controls.Add(this.pbComState);
            this.Controls.Add(this.btnOpenCom);
            this.Controls.Add(this.cbStopBits);
            this.Controls.Add(this.lbStopBits);
            this.Controls.Add(this.cbDataBits);
            this.Controls.Add(this.lbDataBits);
            this.Controls.Add(this.cbParity);
            this.Controls.Add(this.lbParity);
            this.Controls.Add(this.cbBaudRate);
            this.Controls.Add(this.lbBaundRate);
            this.Controls.Add(this.cbPortName);
            this.Controls.Add(this.lbPortName);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox4);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "MainWindow";
            this.Text = "Gas_Sensors";
            this.Load += new System.EventHandler(this.MainWindow_Load);
            ((System.ComponentModel.ISupportInitialize)(this.pbComState)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label lbPortName;
        private System.Windows.Forms.ComboBox cbPortName;
        private System.Windows.Forms.ComboBox cbBaudRate;
        private System.Windows.Forms.Label lbBaundRate;
        private System.Windows.Forms.ComboBox cbParity;
        private System.Windows.Forms.Label lbParity;
        private System.Windows.Forms.ComboBox cbDataBits;
        private System.Windows.Forms.Label lbDataBits;
        private System.Windows.Forms.ComboBox cbStopBits;
        private System.Windows.Forms.Label lbStopBits;
        private System.Windows.Forms.Button btnOpenCom;
        private System.Windows.Forms.PictureBox pbComState;
        private System.Windows.Forms.TextBox tbReceive;
        private System.Windows.Forms.TextBox tbSend;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label lbSystemTime;
        private System.Windows.Forms.TextBox txtHumiValue;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.TextBox txtTempValue;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.TextBox txtCOValue;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.TextBox txtCO2Value;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.TextBox txtCH2OValue;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.TextBox txtTVOCValue;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TextBox txtPM10Value;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox txtPM25Value;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.CheckBox ck16View;
        private System.Windows.Forms.CheckBox ck16Send;
        private System.Windows.Forms.Button btSend;
        private System.Windows.Forms.Button btnCleartbRece;
        private System.Windows.Forms.Button btnCleartbSend;
        private System.Windows.Forms.CheckBox ckAutoSend;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.TextBox tbIntervalTime;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.GroupBox groupBox4;
    }
}

