using Avalonia.Data.Converters;
using Avalonia.Media;
using System;
using System.Globalization;

namespace SchematicEditor.ViewModels
{
    public class ValueConvertColor : IValueConverter
    {
        public object? Convert(object? value, Type targetType, object? parameter, CultureInfo culture)
        {
            if (value == null) return new SolidColorBrush(Colors.Black);
            if (value is int status && targetType.IsAssignableTo(typeof(IBrush)))
            {
                if (status == 1) return new SolidColorBrush(Colors.ForestGreen);
                else if (status == 0) return new SolidColorBrush(Colors.Black);
            }
            throw new NotImplementedException();
        }

        public object? ConvertBack(object? value, Type targetType, object? parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
}
