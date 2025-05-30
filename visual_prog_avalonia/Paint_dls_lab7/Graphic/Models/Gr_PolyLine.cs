﻿using System.Collections.ObjectModel;

namespace Graphic.Models
{
    public class Gr_PolyLine : IFigure
    {
        private ObservableCollection<Avalonia.Point> point_colection;
        private string save;
        public ObservableCollection<Avalonia.Point> Point_colection
        {
            get => point_colection;
            set => SetAndRaise(ref point_colection, value);
        }
        public string save_point { get => save; set => SetAndRaise(ref save, value); }
        public Gr_PolyLine(string nname, string temp_points, string stroke_color, double stroke_thic) : base(nname, stroke_thic, stroke_color)
        {
            save_point = temp_points;
            Point_colection = Create_colection(temp_points);
            Pos = point_colection[0];
        }

        private ObservableCollection<Avalonia.Point> Create_colection(string temp_all_point)
        {
            string temp_point = string.Empty;
            Avalonia.Point point;
            ObservableCollection<Avalonia.Point> col_point = new ObservableCollection<Avalonia.Point>();
            for (int i = 0; i < temp_all_point.Length; i++)
            {
                if (temp_all_point[i] != ' ') temp_point += temp_all_point[i];
                else
                {
                    point = Avalonia.Point.Parse(temp_point);
                    col_point.Add(point);
                    temp_point = string.Empty;
                }
                if (temp_all_point[i] != ' ' && i == temp_all_point.Length - 1)
                {
                    point = Avalonia.Point.Parse(temp_point);
                    col_point.Add(point);
                    temp_point = string.Empty;
                }
            }
            return col_point;
        }



        // transform 
        public double AngleRT { get; set; }
        public double RTX { get; set; }
        public double RTY { get; set; }
        public double STX { get; set; }
        public double STY { get; set; }
        public double AngleSTX { get; set; }
        public double AngleSTY { get; set; }

        public void Gr_Polyline_transform(string angle_rt, string rt, string st, string angle_st)
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
    }
}
