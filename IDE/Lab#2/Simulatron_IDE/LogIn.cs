using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Data.SqlClient;

namespace Simulatron_IDE
{
    public partial class LogIn : Form
    {
        SqlConnection con = new SqlConnection(@"Data Source=(LocalDB)\v11.0;AttachDbFilename=C:\Users\mitzelu\Documents\Data.mdf;Integrated Security=True;Connect Timeout=30");

        public LogIn()
        {
            InitializeComponent();
        }

        private void enter_Click(object sender, EventArgs e)
        {
            con.Open();
            //SqlDataAdapter sda = new SqlDataAdapter("Select Count(*) From Login where USERNAME='"+ textUser.Text + "' and PASSWORD = '"+ textPass.Text +"' ", con);

            SqlCommand cmd = con.CreateCommand();
            cmd.CommandType = CommandType.Text;
            cmd.CommandText = "Select * From Login where USERNAME='"+ textUser.Text + "' and PASSWORD = '"+ textPass.Text +"'" ;
            cmd.ExecuteNonQuery();

            DataTable dt = new DataTable();
            SqlDataAdapter da = new SqlDataAdapter(cmd);
            da.Fill(dt);

            foreach (DataRow dr in dt.Rows )
            {
                    timer1.Enabled = true;
            
            }

            con.Close();

           /* if (dt.Rows[0][0].ToString() == "1")
            {
                this.Hide();
                Form1 ss = new Form1();
                ss.Show();
            }*/


        }

        private void exit_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void progressBar1_Click(object sender, EventArgs e)
        {

        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            progressBar1.Value = Convert.ToInt32(progressBar1.Value) + 10;

            if (Convert.ToInt32(progressBar1.Value) > 90)
            {
                timer1.Enabled = false;
                this.Hide();
                Form1 ss = new Form1();
                ss.Show();
            }

        }
    }
}
