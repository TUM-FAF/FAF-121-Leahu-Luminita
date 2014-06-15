namespace Simulatron_IDE
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.picture = new System.Windows.Forms.PictureBox();
            this.detected = new System.Windows.Forms.Label();
            this.nr = new System.Windows.Forms.Label();
            this.timer_show = new System.Windows.Forms.Label();
            this.button2 = new System.Windows.Forms.Button();
            this.get_info = new System.Windows.Forms.Button();
            this.reset = new System.Windows.Forms.Button();
            this.name = new System.Windows.Forms.Label();
            this.planet = new System.Windows.Forms.Label();
            this.danger = new System.Windows.Forms.Label();
            this.time_destroy = new System.Windows.Forms.Label();
            this.name_input = new System.Windows.Forms.Label();
            this.planet_input = new System.Windows.Forms.Label();
            this.danger_input = new System.Windows.Forms.Label();
            this.seconds = new System.Windows.Forms.Label();
            this.captured = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.color = new System.Windows.Forms.PictureBox();
            ((System.ComponentModel.ISupportInitialize)(this.picture)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.color)).BeginInit();
            this.SuspendLayout();
            // 
            // timer1
            // 
            this.timer1.Interval = 1000;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick_1);
            // 
            // picture
            // 
            this.picture.BackColor = System.Drawing.Color.Transparent;
            this.picture.Location = new System.Drawing.Point(269, 97);
            this.picture.Name = "picture";
            this.picture.Size = new System.Drawing.Size(167, 169);
            this.picture.SizeMode = System.Windows.Forms.PictureBoxSizeMode.CenterImage;
            this.picture.TabIndex = 0;
            this.picture.TabStop = false;
            // 
            // detected
            // 
            this.detected.AutoSize = true;
            this.detected.BackColor = System.Drawing.Color.Transparent;
            this.detected.Font = new System.Drawing.Font("Magneto", 18F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.detected.ForeColor = System.Drawing.SystemColors.ControlDark;
            this.detected.Location = new System.Drawing.Point(221, 18);
            this.detected.Name = "detected";
            this.detected.Size = new System.Drawing.Size(257, 28);
            this.detected.TabIndex = 1;
            this.detected.Text = "No aliens detected";
            this.detected.Click += new System.EventHandler(this.detected_Click);
            // 
            // nr
            // 
            this.nr.AutoSize = true;
            this.nr.BackColor = System.Drawing.Color.Transparent;
            this.nr.Font = new System.Drawing.Font("Hobo Std", 9.749999F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.nr.ForeColor = System.Drawing.Color.White;
            this.nr.Location = new System.Drawing.Point(553, 151);
            this.nr.Name = "nr";
            this.nr.Size = new System.Drawing.Size(16, 18);
            this.nr.TabIndex = 4;
            this.nr.Text = "0";
            // 
            // timer_show
            // 
            this.timer_show.AutoSize = true;
            this.timer_show.BackColor = System.Drawing.Color.Transparent;
            this.timer_show.Font = new System.Drawing.Font("Hobo Std", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.timer_show.ForeColor = System.Drawing.SystemColors.Desktop;
            this.timer_show.Location = new System.Drawing.Point(44, 47);
            this.timer_show.Name = "timer_show";
            this.timer_show.Size = new System.Drawing.Size(0, 30);
            this.timer_show.TabIndex = 7;
            // 
            // button2
            // 
            this.button2.BackColor = System.Drawing.Color.Transparent;
            this.button2.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("button2.BackgroundImage")));
            this.button2.Font = new System.Drawing.Font("Hobo Std", 9.749999F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.button2.ForeColor = System.Drawing.SystemColors.Desktop;
            this.button2.Location = new System.Drawing.Point(167, 296);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(81, 53);
            this.button2.TabIndex = 8;
            this.button2.Text = "Capture";
            this.button2.UseVisualStyleBackColor = false;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // get_info
            // 
            this.get_info.BackColor = System.Drawing.SystemColors.ControlLight;
            this.get_info.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.get_info.Font = new System.Drawing.Font("Hobo Std", 9.749999F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.get_info.ForeColor = System.Drawing.SystemColors.Desktop;
            this.get_info.Image = ((System.Drawing.Image)(resources.GetObject("get_info.Image")));
            this.get_info.Location = new System.Drawing.Point(294, 324);
            this.get_info.Name = "get_info";
            this.get_info.Size = new System.Drawing.Size(109, 35);
            this.get_info.TabIndex = 9;
            this.get_info.Text = "Find  /  Get Info";
            this.get_info.UseVisualStyleBackColor = false;
            this.get_info.Click += new System.EventHandler(this.get_info_Click);
            // 
            // reset
            // 
            this.reset.BackColor = System.Drawing.Color.Transparent;
            this.reset.Font = new System.Drawing.Font("Hobo Std", 9.749999F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.reset.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.reset.Image = ((System.Drawing.Image)(resources.GetObject("reset.Image")));
            this.reset.Location = new System.Drawing.Point(456, 296);
            this.reset.Name = "reset";
            this.reset.Size = new System.Drawing.Size(81, 53);
            this.reset.TabIndex = 11;
            this.reset.Text = "Reset";
            this.reset.UseVisualStyleBackColor = false;
            this.reset.Click += new System.EventHandler(this.reset_Click);
            // 
            // name
            // 
            this.name.AutoSize = true;
            this.name.BackColor = System.Drawing.Color.Transparent;
            this.name.Font = new System.Drawing.Font("Hobo Std", 9.749999F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.name.ForeColor = System.Drawing.SystemColors.Info;
            this.name.Location = new System.Drawing.Point(59, 114);
            this.name.Name = "name";
            this.name.Size = new System.Drawing.Size(63, 18);
            this.name.TabIndex = 13;
            this.name.Text = "N a m e :";
            this.name.Click += new System.EventHandler(this.info_Click);
            // 
            // planet
            // 
            this.planet.AutoSize = true;
            this.planet.BackColor = System.Drawing.Color.Transparent;
            this.planet.Font = new System.Drawing.Font("Hobo Std", 9.749999F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.planet.ForeColor = System.Drawing.SystemColors.Info;
            this.planet.Location = new System.Drawing.Point(46, 151);
            this.planet.Name = "planet";
            this.planet.Size = new System.Drawing.Size(75, 18);
            this.planet.TabIndex = 14;
            this.planet.Text = "P l a n e t :";
            // 
            // danger
            // 
            this.danger.AutoSize = true;
            this.danger.BackColor = System.Drawing.Color.Transparent;
            this.danger.Font = new System.Drawing.Font("Hobo Std", 9.749999F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.danger.ForeColor = System.Drawing.SystemColors.InactiveCaptionText;
            this.danger.Location = new System.Drawing.Point(39, 182);
            this.danger.Name = "danger";
            this.danger.Size = new System.Drawing.Size(81, 18);
            this.danger.TabIndex = 15;
            this.danger.Text = "D a n g e r :";
            // 
            // time_destroy
            // 
            this.time_destroy.AutoSize = true;
            this.time_destroy.BackColor = System.Drawing.Color.Transparent;
            this.time_destroy.Font = new System.Drawing.Font("Hobo Std", 9.749999F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.time_destroy.ForeColor = System.Drawing.SystemColors.InactiveCaptionText;
            this.time_destroy.Location = new System.Drawing.Point(34, 210);
            this.time_destroy.Name = "time_destroy";
            this.time_destroy.Size = new System.Drawing.Size(165, 18);
            this.time_destroy.TabIndex = 16;
            this.time_destroy.Text = "T i m e   to   c a p t u r e :";
            // 
            // name_input
            // 
            this.name_input.AutoSize = true;
            this.name_input.BackColor = System.Drawing.Color.Transparent;
            this.name_input.Font = new System.Drawing.Font("Hobo Std", 9.749999F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.name_input.ForeColor = System.Drawing.SystemColors.Info;
            this.name_input.Location = new System.Drawing.Point(135, 114);
            this.name_input.Name = "name_input";
            this.name_input.Size = new System.Drawing.Size(0, 18);
            this.name_input.TabIndex = 17;
            // 
            // planet_input
            // 
            this.planet_input.AutoSize = true;
            this.planet_input.BackColor = System.Drawing.Color.Transparent;
            this.planet_input.Font = new System.Drawing.Font("Hobo Std", 9.749999F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.planet_input.ForeColor = System.Drawing.SystemColors.Info;
            this.planet_input.Location = new System.Drawing.Point(135, 148);
            this.planet_input.Name = "planet_input";
            this.planet_input.Size = new System.Drawing.Size(0, 18);
            this.planet_input.TabIndex = 18;
            // 
            // danger_input
            // 
            this.danger_input.AutoSize = true;
            this.danger_input.BackColor = System.Drawing.Color.Transparent;
            this.danger_input.Font = new System.Drawing.Font("Hobo Std", 9.749999F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.danger_input.ForeColor = System.Drawing.SystemColors.InactiveCaptionText;
            this.danger_input.Location = new System.Drawing.Point(135, 182);
            this.danger_input.Name = "danger_input";
            this.danger_input.Size = new System.Drawing.Size(0, 18);
            this.danger_input.TabIndex = 19;
            // 
            // seconds
            // 
            this.seconds.AutoSize = true;
            this.seconds.BackColor = System.Drawing.Color.Transparent;
            this.seconds.Font = new System.Drawing.Font("Hobo Std", 9.749999F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.seconds.ForeColor = System.Drawing.SystemColors.InactiveCaptionText;
            this.seconds.Location = new System.Drawing.Point(122, 248);
            this.seconds.Name = "seconds";
            this.seconds.Size = new System.Drawing.Size(0, 18);
            this.seconds.TabIndex = 20;
            // 
            // captured
            // 
            this.captured.AutoSize = true;
            this.captured.BackColor = System.Drawing.Color.Transparent;
            this.captured.Font = new System.Drawing.Font("Hobo Std", 9.749999F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.captured.ForeColor = System.Drawing.Color.White;
            this.captured.Location = new System.Drawing.Point(553, 248);
            this.captured.Name = "captured";
            this.captured.Size = new System.Drawing.Size(16, 18);
            this.captured.TabIndex = 21;
            this.captured.Text = "0";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.BackColor = System.Drawing.Color.Transparent;
            this.label1.Font = new System.Drawing.Font("Hobo Std", 9.749999F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.ForeColor = System.Drawing.SystemColors.Info;
            this.label1.Location = new System.Drawing.Point(474, 114);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(167, 18);
            this.label1.TabIndex = 22;
            this.label1.Text = "D e t e c t e d   a l i e n s :";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.BackColor = System.Drawing.Color.Transparent;
            this.label2.Font = new System.Drawing.Font("Hobo Std", 9.749999F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.ForeColor = System.Drawing.SystemColors.Info;
            this.label2.Location = new System.Drawing.Point(488, 209);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(169, 18);
            this.label2.TabIndex = 23;
            this.label2.Text = "C a p t u r e d   a l i e n s :";
            // 
            // color
            // 
            this.color.BackColor = System.Drawing.Color.Transparent;
            this.color.Location = new System.Drawing.Point(571, 1);
            this.color.Name = "color";
            this.color.Size = new System.Drawing.Size(111, 110);
            this.color.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.color.TabIndex = 24;
            this.color.TabStop = false;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("$this.BackgroundImage")));
            this.ClientSize = new System.Drawing.Size(696, 371);
            this.Controls.Add(this.color);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.captured);
            this.Controls.Add(this.seconds);
            this.Controls.Add(this.danger_input);
            this.Controls.Add(this.planet_input);
            this.Controls.Add(this.name_input);
            this.Controls.Add(this.time_destroy);
            this.Controls.Add(this.danger);
            this.Controls.Add(this.planet);
            this.Controls.Add(this.name);
            this.Controls.Add(this.reset);
            this.Controls.Add(this.get_info);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.timer_show);
            this.Controls.Add(this.nr);
            this.Controls.Add(this.detected);
            this.Controls.Add(this.picture);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.MinimumSize = new System.Drawing.Size(695, 372);
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Simalatron";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.picture)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.color)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.PictureBox picture;
        private System.Windows.Forms.Label detected;
        private System.Windows.Forms.Label nr;
        private System.Windows.Forms.Label timer_show;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button get_info;
        private System.Windows.Forms.Button reset;
        private System.Windows.Forms.Label name;
        private System.Windows.Forms.Label planet;
        private System.Windows.Forms.Label danger;
        private System.Windows.Forms.Label time_destroy;
        private System.Windows.Forms.Label name_input;
        private System.Windows.Forms.Label planet_input;
        private System.Windows.Forms.Label danger_input;
        private System.Windows.Forms.Label seconds;
        private System.Windows.Forms.Label captured;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.PictureBox color;
    }
}

