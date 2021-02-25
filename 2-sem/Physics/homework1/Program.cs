using System;
using System.Windows.Forms;
using System.Windows.Forms.DataVisualization.Charting;

namespace Physics
{
    public class Physics : Form
    {
        private System.ComponentModel.IContainer components = null;
        Chart chart1;

        public Physics()
        {
            InitializeComponent();
        }
        public const double g = 9.80665;
        public static double ConvertRadiansToDegrees(double radians)
        {
            double degrees = (180 / Math.PI) * radians;
            return (degrees);
        }
        
        public static double ConvertDegreesToRadian(double degrees)
        {
            double radians = (Math.PI / 180) * degrees;
            return radians;
        }
        public double Hmax(double v, double a)
        {
            return Math.Round(Math.Pow(v * Math.Sin(a), 2) / (2 * g));
        }
        public double Smax(double v, double a)
        {
            return Math.Round(Math.Pow(v, 2) * Math.Sin(2 * a) / g, 2);
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            chart1.Series.Clear();
            var series1 = new Series
            {
                Name = "Series1",
                Color = System.Drawing.Color.Blue,
                IsVisibleInLegend = false,
                IsXValueIndexed = true,
                ChartType = SeriesChartType.Line
            };

            chart1.Series.Add(series1);
            int velocity = 100;
            for (double degree = 0; degree <= 90; degree++)
            {
                double radian = ConvertDegreesToRadian(degree);
                chart1.Series[0].Points.AddXY(Hmax(velocity, radian), Smax(velocity, radian));
            }
            chart1.Invalidate();
        }

        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        private void InitializeComponent()
        {
            components = new System.ComponentModel.Container();
            ChartArea chartArea1 = new ChartArea();
            Legend legend1 = new Legend();
            chart1 = new Chart();
            ((System.ComponentModel.ISupportInitialize)(chart1)).BeginInit();
            SuspendLayout();
            //
            // chart1
            //
            chartArea1.Name = "ChartArea1";
            chart1.ChartAreas.Add(chartArea1);
            chart1.Dock = DockStyle.Fill;
            legend1.Name = "Legend1";
            chart1.Legends.Add(legend1);
            chart1.Location = new System.Drawing.Point(0, 0);
            chart1.Name = "chart1";
            chart1.TabIndex = 0;
            chart1.Text = "chart1";
            //
            // Form1
            //
            AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new System.Drawing.Size(400, 300);
            Controls.Add(chart1);
            Name = "Form1";
            Text = "Physics";
            Load += new EventHandler(Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(chart1)).EndInit();
            ResumeLayout(false);
        }

        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Physics());
        }
    }
}