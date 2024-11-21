using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class EndMes : MonoBehaviour
{

	public string PanelType;
   public Text coinCount;
   public Text MessagePanel;
   public int curentLvl;
   
   void Start(){
		int curentMaxScore=0;
		curentMaxScore=PlayerPrefs.GetInt(("lvl"+curentLvl.ToString()));
		switch(PanelType){
			case "die":
				MessagePanel.text="You die.\nScore - "+coinCount.text;
				break;
			case "win":
				MessagePanel.text="You win.\nScore - "+coinCount.text;
				if(curentMaxScore<PlayerPrefs.GetInt("coins")) PlayerPrefs.SetInt(("lvl"+curentLvl.ToString()),PlayerPrefs.GetInt("coins"));
				break;
		}
	}
}
