using Avalonia.Media;

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
    }
}
