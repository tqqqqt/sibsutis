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
    public class SportViewModel : ViewModelBase
    {
        ObservableCollection<CityEvent> sport_colections;
        public SportViewModel(ObservableCollection<CityEvent> full_col)
        {
            sport_colections = new ObservableCollection<CityEvent>();
            var mas = full_col;
            for (int i = 0; i < full_col.Count(); i++)
            {
                if (mas[i].Category.Contains("Спорт")==true || mas[i].Category.Contains("спорт")==true)
                {
                    if (mas[i].Description.Length > 134)
                    {
                        mas[i].Description.Remove(135);
                        mas[i].Description += "...";
                    }
                    sport_colections.Add(new CityEvent
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

        public ObservableCollection<CityEvent> Sport_colections
        {
            get => sport_colections;
            set
            {
                this.RaiseAndSetIfChanged(ref sport_colections, value);
            }
        }
    }
}
