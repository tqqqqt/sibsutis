using Avalonia.Media;
using DynamicData.Binding;

namespace Graphic.Models
{
    public abstract class IFigure : AbstractNotifyPropertyChanged
    {
        private string name;
        private double strokeThic;
        public SolidColorBrush strokeColor;
        public string Name { get => name; set => SetAndRaise(ref name, value); }
        public double StrokeThic { get => strokeThic; set => SetAndRaise(ref strokeThic, value); }
        public SolidColorBrush StrokeColor { get => strokeColor; set => SetAndRaise(ref strokeColor, value); }

        public IFigure(string nname, double thic, string color)
        {
            Name = nname;
            StrokeThic = thic;
            StrokeColor = SolidColorBrush.Parse(color);
        }
    }
}
