using Avalonia;
using Avalonia.Controls.Primitives;

namespace SchematicEditor.Views.SchemaElements
{
    public class SchemaElementOUT : TemplatedControl
    {
        public static readonly StyledProperty<string> TextOUTProperty =
            AvaloniaProperty.Register<SchemaElementOUT, string>("TextOUT");

        public string TextOUT
        {
            get => GetValue(TextOUTProperty);
            set => SetValue(TextOUTProperty, value);
        }
    }
}
