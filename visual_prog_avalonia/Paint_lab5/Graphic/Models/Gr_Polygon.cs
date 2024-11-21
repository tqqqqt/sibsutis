using Avalonia.Media;
using System.Collections.ObjectModel;

namespace Graphic.Models
{
    public class Gr_Polygon : IFigure
    {
        ObservableCollection<Avalonia.Point> points_colection;
        public ObservableCollection<Avalonia.Point> Point_colection
        {
            get => points_colection;
        }
        public SolidColorBrush Fill { get; set; }
        public string save_point { get; set; }
        public string Name { get; set; }
        public double StrokeThic { get; set; }
        public SolidColorBrush StrokeColor { get; set; }

        public Gr_Polygon(string name, string temp_point, string stroke_color, double stroke_thic, string fill)
        {
            Name = name;
            StrokeThic = stroke_thic;
            StrokeColor = SolidColorBrush.Parse(stroke_color);
            Fill = SolidColorBrush.Parse(fill);
            save_point = temp_point;
            points_colection = CreatePoint(temp_point);
        }

        private ObservableCollection<Avalonia.Point> CreatePoint(string temp_all_point)
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
    }
}
