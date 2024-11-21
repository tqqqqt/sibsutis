using Avalonia.Data.Converters;
using System;
using System.Globalization;

namespace ShemaPaint.ViewModels
{
    public class TenPosConvertor : IValueConverter
    {
        public object? Convert(object? value, Type targetType, object? parameter, CultureInfo culture)
        {
            if (value == null) return null;

            if (value is int valueConvertInt)
            {
                var newValue = valueConvertInt - 10;
                return newValue;
            }
            else if (value is double valueConvertDouble)
            {
                var newValue = valueConvertDouble - 10;
                return newValue;
            }
            throw new NotSupportedException();
        }

        public object? ConvertBack(object? value, Type targetType, object? parameter, CultureInfo culture)
        {
            throw new NotSupportedException();
        }
    }
}
