﻿using Avalonia.Media;

namespace Graphic.Models
{
    public class Gr_Path : IFigure
    {
        public string Name { get; set; }
        public double StrokeThic { get; set; }
        public SolidColorBrush StrokeColor { get; set; }
        public SolidColorBrush Fill { get; set; }
        public Geometry Points { get; set; }
        public string save_points { get; set; }

        public Gr_Path(string name, string temp_point, string stroke, double stroke_thic, string fill)
        {
            Name = name;
            StrokeThic = stroke_thic;
            StrokeColor = SolidColorBrush.Parse(stroke);
            Fill = SolidColorBrush.Parse(fill);
            save_points = temp_point;
            Points = Geometry.Parse(temp_point);
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
    }
}
