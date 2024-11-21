using Avalonia.Media;

namespace Graphic.Models
{
    public interface IFigure
    {
        string Name { get; set; }
        double StrokeThic { get; set; }
        SolidColorBrush StrokeColor { get; set; }


        // transform 
        double AngleRT { get; set; }
        double RTX { get; set; }
        double RTY { get; set; }
        double STX { get; set; }
        double STY { get; set; }
        double AngleSTX { get; set; }
        double AngleSTY { get; set; }
    }
}
