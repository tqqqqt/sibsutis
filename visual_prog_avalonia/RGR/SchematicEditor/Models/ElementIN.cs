namespace SchematicEditor.Models
{
    public class ElementIN : ISchemaElement
    {
        private int status;

        public ElementIN()
        {
            Status = 0;
            OutSignal = Status;
        }

        public int Status
        {
            get => status;
            set
            {
                SetAndRaise(ref status, value);
                OutSignal = Status;
            }
        }

        public void ChangeInStatus()
        {
            Status = (Status == 0) ? 1 : 0;
        }
    }
}
