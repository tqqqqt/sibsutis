namespace Graphic.Models
{
    public class Gr_Line : IFigure
    {
        private Avalonia.Point start, end;
        public Avalonia.Point StartPoint { get => start; set => SetAndRaise(ref start, value); }
        public Avalonia.Point EndPoint { get => end; set => SetAndRaise(ref end, value); }


        public double DX { get; set; }
        public double DY { get; set; }


        public Gr_Line(string nname, double stroke_thic, string stroke, string sstart, string eend) : base(nname, stroke_thic, stroke)
        {
            StartPoint = Avalonia.Point.Parse(sstart);
            EndPoint = Avalonia.Point.Parse(eend);
            Pos = StartPoint;
            DX = EndPoint.X - StartPoint.X;
            DY = EndPoint.Y - StartPoint.Y;
        }


        // transform 
        public double AngleRT { get; set; }
        public double RTX { get; set; }
        public double RTY { get; set; }
        public double STX { get; set; }
        public double STY { get; set; }
        public double AngleSTX { get; set; }
        public double AngleSTY { get; set; }

        public void Gr_Line_transform(string angle_rt, string rt, string st, string angle_st)
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

        public void UpdateMove()
        {
            StartPoint = new Avalonia.Point(Pos.X, Pos.Y);
            EndPoint = new Avalonia.Point(
            Pos.X + DX, Pos.Y + DY);
        }
    }
}
