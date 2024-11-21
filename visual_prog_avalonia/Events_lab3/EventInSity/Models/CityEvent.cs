using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EventInSity.Models
{
    public class CityEvent
    {
        public CityEvent()
        {
            Header = String.Empty;
            Description = String.Empty;
            Image = String.Empty;
            Date = String.Empty;
            Category = String.Empty;
        }
        public string Header { get; set; }
        public string Description { get; set; }
        public string Image { get; set; }
        public string Date { get; set; }
        public string Category { get; set; }
        public int Price { get; set; }
    }
    
}
