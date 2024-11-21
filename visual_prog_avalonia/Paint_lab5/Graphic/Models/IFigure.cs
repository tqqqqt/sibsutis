using Avalonia.Media;

namespace Graphic.Models
{
    public interface IFigure
    {
        string Name { get; set; }
        double StrokeThic { get; set; }
        SolidColorBrush StrokeColor { get; set; }
    }
}
