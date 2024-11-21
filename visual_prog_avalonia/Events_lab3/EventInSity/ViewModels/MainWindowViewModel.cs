using EventInSity.Models;
using EventInSity.ViewModels.Pages;
using EventInSity.Views.Pages;
using ReactiveUI;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using System.Reactive;
using System.Text;
using System.Xml.Serialization;

namespace EventInSity.ViewModels
{
    public class MainWindowViewModel : ViewModelBase
    {
        private object culture_content, education_content, excursions_content, kids_content, lifestyle_content, online_content, party_content, show_content, sport_content;
        private ObservableCollection<ViewModelBase> vmbaseCollection;
        private ObservableCollection<CityEvent> eventCollection;

        public MainWindowViewModel()
        {
            eventCollection = new ObservableCollection<CityEvent>();
            XmlSerializer xs = new XmlSerializer(typeof(ObservableCollection<CityEvent>));
            using (StreamReader rd = new StreamReader(@"..\..\..\events.xml"))
            {
                eventCollection = xs.Deserialize(rd) as ObservableCollection<CityEvent>;
            }


            vmbaseCollection = new ObservableCollection<ViewModelBase>();
            vmbaseCollection.Add(new CultureViewModel(eventCollection));
            vmbaseCollection.Add(new EducationViewModel(eventCollection));
            vmbaseCollection.Add(new ExcursionsViewModel(eventCollection));
            vmbaseCollection.Add(new KidsViewModel(eventCollection));
            vmbaseCollection.Add(new LifestyleViewModel(eventCollection));
            vmbaseCollection.Add(new OnlineViewModel(eventCollection));
            vmbaseCollection.Add(new PartyViewModel(eventCollection));
            vmbaseCollection.Add(new ShowViewModel(eventCollection));
            vmbaseCollection.Add(new SportViewModel(eventCollection));

            culture_content = vmbaseCollection[0];
            education_content = vmbaseCollection[1];
            excursions_content = vmbaseCollection[2];
            kids_content = vmbaseCollection[3];
            lifestyle_content = vmbaseCollection[4];
            online_content = vmbaseCollection[5];
            party_content = vmbaseCollection[6];
            show_content = vmbaseCollection[7];
            sport_content = vmbaseCollection[8];


            //SaveItem = ReactiveCommand.Create(() =>
            // {
            //XmlSerializer xs = new XmlSerializer(typeof(ObservableCollection<CityEvent>));
               // using (StreamWriter wr = new StreamWriter(@"..\..\..\events.xml"))
              //  {
              //      xs.Serialize(wr, eventCollection);
             //   }
           // });
        }

        //public ReactiveCommand<Unit, Unit> SaveItem { get; }


        public object Culture_content { get => culture_content; }
        public object Education_content { get => education_content; }
        public object Excursions_content { get => excursions_content; }
        public object Kids_content{ get => kids_content;}
        public object Lifestyle_content { get => lifestyle_content; }
        public object Online_content { get => online_content; }
        public object Party_Content { get => party_content; }
        public object Show_content { get => show_content; }
        public object Sport_content { get => sport_content; }
    }
}
