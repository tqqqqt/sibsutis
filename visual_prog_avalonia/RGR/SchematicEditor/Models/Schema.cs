using DynamicData.Binding;
using System.Collections.ObjectModel;

namespace SchematicEditor.Models
{
    public class Schema : AbstractNotifyPropertyChanged
    {
        private ObservableCollection<ISchemaObject> elementColection;
        private string name;

        public Schema()
        {
            name = string.Empty;
            elementColection = new ObservableCollection<ISchemaObject>();
        }

        public string Name
        {
            get => name;
            set => SetAndRaise(ref name, value);
        }
        public ObservableCollection<ISchemaObject> ElementColection
        {
            get => elementColection;
            set => SetAndRaise(ref elementColection, value);
        }
    }
}
