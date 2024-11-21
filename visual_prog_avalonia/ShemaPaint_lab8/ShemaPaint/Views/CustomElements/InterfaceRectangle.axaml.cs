using Avalonia;
using Avalonia.Controls.Primitives;
using ShemaPaint.Models;
using System.Collections.ObjectModel;

namespace ShemaPaint.Views.CustomElements
{
    public class InterfaceRectangle : TemplatedControl
    {
        public static readonly StyledProperty<string> NameClassProperty =
            AvaloniaProperty.Register<ClassRectangle, string>("NameClass");
        public static readonly StyledProperty<ObservableCollection<Atrib>> PeremClassProperty =
            AvaloniaProperty.Register<ClassRectangle, ObservableCollection<Atrib>>("PeremClass");
        public static readonly StyledProperty<ObservableCollection<Oper>> OperClassProperty =
            AvaloniaProperty.Register<ClassRectangle, ObservableCollection<Oper>>("OperClass");
        public static readonly StyledProperty<double> FontSizeMainProperty =
            AvaloniaProperty.Register<ClassRectangle, double>("FontSizeMain");


        public string NameClass
        {
            get => GetValue(NameClassProperty);
            set => SetValue(NameClassProperty, value);
        }
        public ObservableCollection<Atrib> PeremClass
        {
            get => GetValue(PeremClassProperty);
            set => SetValue(PeremClassProperty, value);
        }
        public ObservableCollection<Oper> OperClass
        {
            get => GetValue(OperClassProperty);
            set => SetValue(OperClassProperty, value);
        }
        public double FontSizeMain
        {
            get => GetValue(FontSizeMainProperty);
            set => SetValue(FontSizeMainProperty, value);
        }
    }
}
