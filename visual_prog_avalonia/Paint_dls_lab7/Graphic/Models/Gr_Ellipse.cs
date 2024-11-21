using Avalonia.Media;

namespace Graphic.Models
{
    public class Gr_Ellipse : IFigure
    {
        private int width, height;
        private SolidColorBrush fill;
        private Avalonia.Point start;
        public int Width { get => width; set => SetAndRaise(ref width, value); }
        public int Height { get => height; set => SetAndRaise(ref height, value); }
        public SolidColorBrush Fill { get => fill; set => SetAndRaise(ref fill, value); }
        public Avalonia.Point StartPoint { get => start; set => SetAndRaise(ref start, value); }

        public Gr_Ellipse(string nname, int wid, int hei, string temp_point, string stroke_color, double stroke_thic, string fill) : base(nname, stroke_thic, stroke_color)
        {
            Fill = SolidColorBrush.Parse(fill);
            Width = wid;
            Height = hei;
            StartPoint = Avalonia.Point.Parse(temp_point);
        }


        // transform 
        public double AngleRT { get; set; }
        public double RTX { get; set; }
        public double RTY { get; set; }
        public double STX { get; set; }
        public double STY { get; set; }
        public double AngleSTX { get; set; }
        public double AngleSTY { get; set; }

        public void Gr_Ellipse_transform(string angle_rt, string rt, string st, string angle_st)
        {
            AngleRT = double.Parse(angle_rt);
            double x = 0, y = 0;
            break_string(rt, ref x, ref y);
            RTX = x;
            RTY = y;
            break_string(st, ref x, ref y);
            STX = x;
            STY = y;
            break_string(angle_st, ref x, ref y);
            AngleSTX = x;
            AngleSTY = y;
        }
        public void break_string(string temp_all, ref double x, ref double y)
        {
            string temp = string.Empty;
            x = 0;
            y = 0;
            for (int i = 0; i < temp_all.Length; i++)
            {
                if (temp_all[i] != ' ')
                {
                    if (temp_all[i] != '.') temp += temp_all[i];
                    else if (temp_all[i] == '.') temp += ',';
                }
                else if (temp_all[i] == ' ' && temp != null)
                {
                    x = double.Parse(temp);
                    temp = string.Empty;
                }
                if (i == temp_all.Length - 1)
                {
                    y = double.Parse(temp);
                    temp = string.Empty;
                }
            }
        }
    }
}
