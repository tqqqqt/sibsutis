using Avalonia.Controls;
using ShemaPaint.Models;
using ShemaPaint.ViewModels;

namespace ShemaPaint.Views.ChildWindows
{
    public partial class ChangeFormWindow : Window
    {
        public ChangeFormWindow()
        {
            InitializeComponent();
            DataContext = new ChangeFormWindowViewModel();
        }

        public ChangeFormWindow(El_Class elementClass)
        {
            InitializeComponent();
            DataContext = new ChangeFormWindowViewModel(elementClass);
        }

        public ChangeFormWindow(El_Interface elementInterface)
        {
            InitializeComponent();
            DataContext = new ChangeFormWindowViewModel(elementInterface);
        }
    }
}
