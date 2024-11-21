using Avalonia.Media;

namespace Graphic.Models
{
    public class Gr_Ellipse : IFigure
    {
        public string Name { get; set; }
        public double StrokeThic { get; set; }
        public SolidColorBrush StrokeColor { get; set; }
        public int Width { get; set; }
        public int Height { get; set; }
        public SolidColorBrush Fill { get; set; }
        public Avalonia.Point StartPoint { get; set; }

        public Gr_Ellipse(string name, int wid, int hei, string temp_point, string stroke_color, double stroke_thic, string fill)
        {
            Name = name;
            StrokeThic = stroke_thic;
            StrokeColor = SolidColorBrush.Parse(stroke_color);
            Fill = SolidColorBrush.Parse(fill);
            Width = wid;
            Height = hei;
            StartPoint = Avalonia.Point.Parse(temp_point);
        }
    }
}
