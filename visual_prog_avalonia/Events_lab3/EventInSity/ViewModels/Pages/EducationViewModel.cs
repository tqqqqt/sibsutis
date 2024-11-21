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
    public class EducationViewModel:ViewModelBase
    {
        ObservableCollection<CityEvent> education_colections;
        public EducationViewModel(ObservableCollection<CityEvent> full_col)
        {
            education_colections = new ObservableCollection<CityEvent>();
            var mas = full_col;
            for(int i = 0; i < full_col.Count(); i++)
            {
                if (mas[i].Category.Contains("Образование")==true || mas[i].Category.Contains("образование")==true)
                {
                    if (mas[i].Description.Length > 134)
                    {
                        mas[i].Description.Remove(135);
                        mas[i].Description += "...";
                    }
                    education_colections.Add(new CityEvent
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

        public ObservableCollection<CityEvent> Education_colections
        {
            get => education_colections;
            set
            {
                this.RaiseAndSetIfChanged(ref education_colections, value);
            }
        }
    }
}
