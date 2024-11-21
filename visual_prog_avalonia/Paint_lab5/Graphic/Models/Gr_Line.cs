using Avalonia.Media;

namespace Graphic.Models
{
    public class Gr_Line : IFigure
    {
        public string Name { get; set; }
        public double StrokeThic { get; set; }
        public SolidColorBrush StrokeColor { get; set; }
        public Avalonia.Point StartPoint { get; set; }
        public Avalonia.Point EndPoint { get; set; }


        public Gr_Line(string name, double stroke_thic, string stroke, string start, string end)
        {
            Name = name;
            StrokeThic = stroke_thic;
            StrokeColor = SolidColorBrush.Parse(stroke);
            StartPoint = Avalonia.Point.Parse(start);
            EndPoint = Avalonia.Point.Parse(end);
        }
    }
}
