using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class LvlMes : MonoBehaviour
{
    public int lvlNum;
    public Text messPanel;
    
    void Start(){
    	int temp=0;
    	switch(lvlNum){
    		case 1:
    			temp=PlayerPrefs.GetInt("lvl1");
    			if(temp==0 || (temp<0 || temp>7)) temp=0;
    			messPanel.text=temp.ToString()+"/7";
    			break;
    		case 2:
    			temp=PlayerPrefs.GetInt("lvl2");
    			if(temp==0 || (temp<0 || temp>7)) temp=0;
    			messPanel.text=temp.ToString()+"/7";
    			break;
    		case 3:
    			temp=PlayerPrefs.GetInt("lvl3");
    			if(temp==0 || (temp<0 || temp>7)) temp=0;
    			messPanel.text=temp.ToString()+"/7";
    			break;
    	}
    }
}
