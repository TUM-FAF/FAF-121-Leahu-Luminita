using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Media;

namespace Simulatron_IDE
{
    public partial class Form1 : Form
    {
        private SoundPlayer sound_play;

        public Form1()
        {                  
            InitializeComponent();
            sound_play = new SoundPlayer("Alert sound.wav");

        }

        private void richTextBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void label3_Click(object sender, EventArgs e)
        {

        }
    
        int i = 0;
        int sec;
        private void timer1_Tick(object sender, EventArgs e)
        {
            i++;
            
        }

        private void get_info_Click(object sender, EventArgs e)
        {
            Random rand = new Random();
            int r = rand.Next(-1, 5);

            string[] gif_URL = {"https://raw.githubusercontent.com/TUM-FAF/FAF-121-Leahu-Luminita/master/IDE/Lab%232/aliens/allien5-3D.gif", "https://raw.githubusercontent.com/TUM-FAF/FAF-121-Leahu-Luminita/master/IDE/Lab%232/aliens/alien4-3D.gif",
                               "https://raw.githubusercontent.com/TUM-FAF/FAF-121-Leahu-Luminita/master/IDE/Lab%232/aliens/alien-3D.gif", "https://raw.githubusercontent.com/TUM-FAF/FAF-121-Leahu-Luminita/master/IDE/Lab%232/aliens/alien3-3D.gif",
                               "https://raw.githubusercontent.com/TUM-FAF/FAF-121-Leahu-Luminita/master/IDE/Lab%232/aliens/alien2-3D.gif"};

           /* string[] images_URL = {"https://raw.githubusercontent.com/TUM-FAF/FAF-121-Leahu-Luminita/master/IDE/Lab%232/aliens/0000-alien_000.jpg", "https://raw.githubusercontent.com/TUM-FAF/FAF-121-Leahu-Luminita/master/IDE/Lab%232/aliens/al_1.jpg",
                                    "https://raw.githubusercontent.com/TUM-FAF/FAF-121-Leahu-Luminita/master/IDE/Lab%232/aliens/alien%202.jpg", "https://raw.githubusercontent.com/TUM-FAF/FAF-121-Leahu-Luminita/master/IDE/Lab%232/aliens/alien3.png",
                                    "https://raw.githubusercontent.com/TUM-FAF/FAF-121-Leahu-Luminita/master/IDE/Lab%232/aliens/all_1.jpg"};*/

            string[] name = { "I r o n", "M a r b l e", "S t o n e", "U l i f o", "I z u q i" };
            string[] planets = { "V e n u s", "J u p i t e r", "M a r s", "S a t u r n", "N e p t u n e" };
            string[] danger = { "H i g h t", "M e d i u m", "H i g h t", "M e d i u m", "L o w" };
            string[] second = { "7", "9", "5", "11", "13" };
            char charIndex;

                if ((r >= 0) & (r <= 4))
                {
                    i = i + 1;

                    detected.Text = "Alient " + name[r].ToString() + " detected";
                    name_input.Text = name[r].ToString();
                    planet_input.Text = planets[r].ToString();
                    danger_input.Text = danger[r].ToString();
                    seconds.Text = second[r].ToString();
                    picture.ImageLocation = gif_URL[r];
                    nr.Text = i.ToString();

                    if (danger_input.Text == danger[0])
                    {
                        color.ImageLocation = "https://raw.githubusercontent.com/TUM-FAF/FAF-121-Leahu-Luminita/master/IDE/Lab%232/aliens/rosu-extreme.gif";
                        sound_play.Play();
                    }

                    if (danger_input.Text == danger[1])
                    {
                        color.ImageLocation = "https://raw.githubusercontent.com/TUM-FAF/FAF-121-Leahu-Luminita/master/IDE/Lab%232/aliens/galben-medium.gif";
                    }

                    if (danger_input.Text == danger[4])
                    {
                        color.ImageLocation = "https://raw.githubusercontent.com/TUM-FAF/FAF-121-Leahu-Luminita/master/IDE/Lab%232/aliens/verde-minim.gif";
                    }

                    sec = int.Parse(second[r].ToString());
                    timer1.Start();

                }

                else
                {
                    detected.Text = "No aliens detected";
                    name_input.Text = " ";
                    planet_input.Text = " ";
                    danger_input.Text = " ";
                    seconds.Text = " ";
                    picture.Image = null;
                }

                
                nr.Text = i.ToString();

                
        }

      
        private void info_Click(object sender, EventArgs e)
        {

        }

        private void timer1_Tick_1(object sender, EventArgs e)
        {
            if (sec == 0)
            {
                timer1.Stop();
                sound_play.Stop();
                picture.Image = null;
                detected.Text = "No aliens detected";
                name_input.Text = " ";
                planet_input.Text = " ";
                danger_input.Text = " ";
                seconds.Text = " ";
                color.Image = null;
                MessageBox.Show("The alien has escaped", "Time is up !", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);

            }

            if (sec > 0)
            {
                sec -= 1;
                timer_show.Text = sec.ToString();
            }
        }

        private void reset_Click(object sender, EventArgs e)
        {
            sound_play.Stop();
            picture.Image = null;
            nr.Text = "0";
            captured.Text = "0";
            detected.Text = "No aliens detected";
            name_input.Text = " ";
            planet_input.Text = " ";
            danger_input.Text = " ";
            seconds.Text = " ";
            timer1.Stop();
            
            color.Image = null;
            
        }

        int i_captured = 0;
        private void button2_Click(object sender, EventArgs e)
        {
            if (picture.Image == null)
            {
                MessageBox.Show("No alien detected", "System Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            else
            {
                sound_play.Stop();
                timer1.Stop();
                timer_show.Text = "  ";
                i_captured++;
                captured.Text = i_captured.ToString();
                picture.Image = null;
                detected.Text = "No aliens detected";
                name_input.Text = " ";
                planet_input.Text = " ";
                danger_input.Text = " ";
                seconds.Text = " ";
                color.Image = null;
                MessageBox.Show("The alien is captured", "Good job!", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
            }
   

        }

       


    }
}
