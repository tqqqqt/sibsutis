using Avalonia.Media;

namespace Graphic.Models
{
    public class Gr_Rectangle : IFigure
    {
        public double Width { get; set; }
        public double Height { get; set; }
        public SolidColorBrush Fill { get; set; }
        public Avalonia.Point Start_point { get; set; }
        public string Name { get; set; }
        public double StrokeThic { get; set; }
        public SolidColorBrush StrokeColor { get; set; }

        public Gr_Rectangle(string name, string point, double wid, double hei, double stroke_thic, string stroke, string fill)
        {
            Name = name;
            StrokeThic = stroke_thic;
            StrokeColor = SolidColorBrush.Parse(stroke);
            Width = wid;
            Height = hei;
            Fill = SolidColorBrush.Parse(fill);
            Start_point = Avalonia.Point.Parse(point);
        }
    }
}
