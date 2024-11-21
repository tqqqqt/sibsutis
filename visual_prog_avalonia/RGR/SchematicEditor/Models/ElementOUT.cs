namespace SchematicEditor.Models
{
    public class ElementOUT : ISchemaElement
    {
        private int status;

        public ElementOUT()
        {
            status = 0;
        }

        public int Status
        {
            get => status;
            set => SetAndRaise(ref status, value);
        }

        public int InSignal
        {
            get => status;
            set => Status = value;
        }
    }
}
