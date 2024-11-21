using Avalonia;
using Avalonia.Media;

namespace Graphic.Models
{
    public class Gr_Path : IFigure
    {
        private SolidColorBrush fill;
        private Geometry points;
        private string save;
        public SolidColorBrush Fill { get => fill; set => SetAndRaise(ref fill, value); }
        public Geometry Points { get => points; set => SetAndRaise(ref points, value); }
        public string save_points { get => save; set => SetAndRaise(ref save, value); }

        public Gr_Path(string nname, string temp_point, string stroke, double stroke_thic, string fill) : base(nname, stroke_thic, stroke)
        {
            Fill = SolidColorBrush.Parse(fill);
            save_points = temp_point;
            Points = Geometry.Parse(temp_point);
            Pos = FindStart(temp_point);
        }


        // transform 
        public double AngleRT { get; set; }
        public double RTX { get; set; }
        public double RTY { get; set; }
        public double STX { get; set; }
        public double STY { get; set; }
        public double AngleSTX { get; set; }
        public double AngleSTY { get; set; }

        public void Gr_Path_transform(string angle_rt, string rt, string st, string angle_st)
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


        // move (drag)
        private Avalonia.Point pos;
        public Avalonia.Point Pos { get => pos; set => SetAndRaise(ref pos, value); }

        private Avalonia.Point FindStart(string temp_all_point)
        {
            int flag = 0;
            Avalonia.Point poin = Point.Parse("0,0");
            string temp_point = string.Empty;
            for (int i = 0; i < temp_all_point.Length; i++)
            {
                if (flag == 1)
                {
                    temp_point += temp_all_point[i];
                    continue;
                }
                if (temp_all_point[i] == ' ' && flag == 0) flag = 1;
                else if (temp_all_point[i] == ' ' && flag == 1)
                {
                    poin = Point.Parse(temp_point);
                    break;
                }
            }
            return poin;
        }
    }
}
