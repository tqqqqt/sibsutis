using Avalonia;
using Avalonia.Controls.Primitives;

namespace SchematicEditor.Views.SchemaElements
{
    public class SchemaElementIN : TemplatedControl
    {
        public static readonly StyledProperty<string> TextINProperty =
            AvaloniaProperty.Register<SchemaElementIN, string>("TextIN");

        public string TextIN
        {
            get => GetValue(TextINProperty);
            set => SetValue(TextINProperty, value);
        }
    }
}
