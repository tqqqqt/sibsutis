using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Collections.ObjectModel;
using EventInSity.Models;
using Avalonia.Remote.Protocol;
using System.Reflection;
using ReactiveUI;

namespace EventInSity.ViewModels.Pages
{
    public class KidsViewModel : ViewModelBase
    {
        private ObservableCollection<CityEvent> kids_colections;
        public KidsViewModel(ObservableCollection<CityEvent> full_colection)
        {
            kids_colections = new ObservableCollection<CityEvent>();
            var mas = full_colection;
            for(int i = 0; i < full_colection.Count(); i++)
            {
                if (mas[i].Category.Contains("Для детей")==true || mas[i].Category.Contains("для детей")==true)
                {
                    if (mas[i].Description.Length > 134)
                    {
                        mas[i].Description.Remove(135);
                        mas[i].Description += "...";
                    }
                    kids_colections.Add(new CityEvent
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

        public ObservableCollection<CityEvent> Kids_colections
        {
            get { return kids_colections; }
            set
            {
                this.RaiseAndSetIfChanged(ref kids_colections, value);
            }
        }
    }
}
