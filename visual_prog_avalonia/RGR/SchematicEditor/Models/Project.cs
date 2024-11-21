using DynamicData.Binding;
using System.Collections.ObjectModel;

namespace SchematicEditor.Models
{
    public class Project : AbstractNotifyPropertyChanged
    {
        private ObservableCollection<Schema> schemaColection;
        private string name;

        public Project()
        {
            name = string.Empty;
            schemaColection = new ObservableCollection<Schema>
            {
                new Schema
                {
                    Name = "схема 1"
                }
            };
            SchemaColection = schemaColection;
        }

        public string Name
        {
            get => name;
            set => SetAndRaise(ref name, value);
        }

        public ObservableCollection<Schema> SchemaColection
        {
            get => schemaColection;
            set => SetAndRaise(ref schemaColection, value);
        }
    }
}
