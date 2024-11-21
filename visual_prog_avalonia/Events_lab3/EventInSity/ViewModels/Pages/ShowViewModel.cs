using EventInSity.Models;
using ReactiveUI;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EventInSity.ViewModels.Pages
{
    public class ShowViewModel : ViewModelBase
    {
        ObservableCollection<CityEvent> show_colections;
        public ShowViewModel(ObservableCollection<CityEvent> full_col)
        {
            show_colections = new ObservableCollection<CityEvent>();
            var mas = full_col;
            for (int i = 0; i < full_col.Count(); i++)
            {
                if (mas[i].Category.Contains("Шоу")==true || mas[i].Category.Contains("шоу")==true)
                {
                    if (mas[i].Description.Length > 134)
                    {
                        mas[i].Description.Remove(135);
                        mas[i].Description += "...";
                    }
                    show_colections.Add(new CityEvent
                    {
                        Header = mas[i].Header,
                        Description = mas[i].Description,
                        Image = mas[i].Image,
                        Date = mas[i].Date,
                        Category = mas[i].Category,
                        Price = mas[i].Price
                    });
                }
            }
        }

        public ObservableCollection<CityEvent> Show_colections
        {
            get => show_colections;
            set
            {
                this.RaiseAndSetIfChanged(ref show_colections, value);
            }
        }
    }
}
