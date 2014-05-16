using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Lab6
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void helpToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Laboratory work #6, C#", "Information", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }
        
        private void button1_Click(object sender, EventArgs e)
        {
            if (this.textBox1.Text != "")
            {
                listBox1.Items.Add(this.textBox1.Text);
                textBox2.Text = listBox1.Items.Count.ToString();
                this.textBox1.Focus();
                this.textBox1.Clear();
            }
            else
            {
                MessageBox.Show("Plese type a new task and then add it", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                this.textBox1.Focus();
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Info", "Information", MessageBoxButtons.OK, MessageBoxIcon.None);

        }

        private void button3_Click(object sender, EventArgs e)
        {
            if (this.listBox1.SelectedIndex >= 0)
            {
                if (MessageBox.Show("Is this task done?", "Confirmation", MessageBoxButtons.YesNo, MessageBoxIcon.Warning) == DialogResult.Yes)
                {
                    this.listBox1.Items.RemoveAt(this.listBox1.SelectedIndex);
                    textBox2.Text = listBox1.Items.Count.ToString();
                }
                    
            }
         }

        private void button4_Click(object sender, EventArgs e)
        {
            if (MessageBox.Show("Do you want to delete all tasks?", "Confirmation", MessageBoxButtons.YesNo, MessageBoxIcon.Warning) == DialogResult.Yes)
            {
                listBox1.Items.Clear();
                textBox2.Text = listBox1.Items.Count.ToString();
            }
            
        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {
            
        }

        private void button2_Click_1(object sender, EventArgs e)
        {
            if(colorDialog1.ShowDialog() == DialogResult.OK)
            {
                this.listBox1.BackColor = colorDialog1.Color;
            }
            
        }
        
    }
}
