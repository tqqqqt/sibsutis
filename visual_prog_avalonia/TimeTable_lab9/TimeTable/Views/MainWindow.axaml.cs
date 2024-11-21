using Avalonia.Controls;
using Avalonia.Interactivity;
using Avalonia.Media;
using TimeTable.ViewModels;

namespace TimeTable.Views
{
    public partial class MainWindow : Window
    {
        private Button? firstOldButton, secondOldButton;
        private int newNaznach, newDate;
        public MainWindow()
        {
            InitializeComponent();
            DataContext = new MainWindowViewModel();
            firstOldButton = this.Find<Button>("buttonOut");
            firstOldButton.Background = SolidColorBrush.Parse("Black");
            firstOldButton.Foreground = SolidColorBrush.Parse("Orange");
            newNaznach = 1;
            secondOldButton = this.Find<Button>("second");
            secondOldButton.Background = SolidColorBrush.Parse("Black");
            secondOldButton.Foreground = SolidColorBrush.Parse("Orange");
            newDate = 2;
        }

        public void ButtonFirstClick(object sender, RoutedEventArgs eventArgs)
        {
            if(DataContext is MainWindowViewModel viewModel)
            {
                if(firstOldButton != sender as Button)
                {
                    var tempButton = sender as Button;
                    firstOldButton.Background = SolidColorBrush.Parse("Silver");
                    firstOldButton.Foreground = SolidColorBrush.Parse("Black");
                    firstOldButton = sender as Button;
                    tempButton.Background = SolidColorBrush.Parse("Black");
                    tempButton.Foreground = SolidColorBrush.Parse("Orange");
                    newNaznach = (tempButton.Name.Equals("buttonIn"))? 2 : 1;
                    viewModel.CurentColectionUpdate(newNaznach, newDate);
                }
            }
        }

        public void ButtonUpdateClick(object sender, RoutedEventArgs eventArgs)
        {
            if(DataContext is MainWindowViewModel viewModel)
            {
                viewModel.UpdateTableBase();
                viewModel.CurentColectionUpdate(newNaznach, newDate);
            }
        }

        public void ButtonDateClick(object sender, RoutedEventArgs eventArgs)
        {
            if(DataContext is MainWindowViewModel viewModel)
            {
                if(secondOldButton != sender as Button)
                {
                    var tempButton = sender as Button;
                    secondOldButton.Background = SolidColorBrush.Parse("Silver");
                    secondOldButton.Foreground = SolidColorBrush.Parse("Black");
                    secondOldButton = sender as Button;
                    tempButton.Background = SolidColorBrush.Parse("Black");
                    tempButton.Foreground = SolidColorBrush.Parse("Orange");
                    if (tempButton.Name.Equals("first") == true) newDate = 1;
                    else if (tempButton.Name.Equals("second") == true) newDate = 2;
                    else newDate = 3;
                    viewModel.CurentColectionUpdate(newNaznach, newDate);
                }
            }
        }
    }
}