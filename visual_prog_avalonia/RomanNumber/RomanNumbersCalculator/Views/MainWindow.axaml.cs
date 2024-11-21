using Avalonia.Controls;
using RomanNumbersCalculator.ViewModels;

namespace RomanNumbersCalculator.Views
{
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            DataContext = new MainWindowViewModel();
        }
    }
}
