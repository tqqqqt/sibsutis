using Avalonia.Controls;
using ShemaPaint.Models;
using ShemaPaint.ViewModels;

namespace ShemaPaint.Views.ChildWindows
{
    public partial class ChangeOption : Window
    {
        public ChangeOption(El_Class changeElement)
        {
            InitializeComponent();
            DataContext = new ChangeOptionWindowViewModel(changeElement);
        }

        public ChangeOption(El_Interface changeElement)
        {
            InitializeComponent();
            DataContext = new ChangeOptionWindowViewModel(changeElement);
        }

        public ChangeOption()
        {
            InitializeComponent();
            DataContext = new ChangeOptionWindowViewModel();
        }
    }
}
