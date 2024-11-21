using DynamicData.Binding;

namespace ShemaPaint.Models
{
    public abstract class IFigures : AbstractNotifyPropertyChanged
    {
        protected Avalonia.Point startPoint;
    }
}
