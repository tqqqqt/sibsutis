using Avalonia.Data.Converters;
using Avalonia.Media;
using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Student.ViewModels
{
    public class ValueConvert : IValueConverter
    {
        public object? Convert(object? value, Type targetType, object? parameter, CultureInfo culture)
        {
            if (value == null) return null;
            if(value is int score && targetType.IsAssignableTo(typeof(IBrush)))
            {
                if (score <= 0) return new SolidColorBrush(Colors.Red);
                else if (score == 1) return new SolidColorBrush(Colors.Yellow);
                else if (score == 2) return new SolidColorBrush(Colors.Green);
            }
            else if(value is double score2 && targetType.IsAssignableTo(typeof(IBrush)))
            {
                if (score2 < 1) return new SolidColorBrush(Colors.Red);
                else if (score2 >= 1 && score2 <= 1.5) return new SolidColorBrush(Colors.Yellow);
                else return new SolidColorBrush(Colors.Green);
            }
            throw new NotImplementedException();
        }

        public object? ConvertBack(object? value, Type targetType, object? parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
}
