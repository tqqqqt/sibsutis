using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class Bonus : MonoBehaviour
{
	[SerializeField] private GameObject DiePanel;
	[SerializeField] private GameObject EndPanel;
	
	public string bonusName;
	public Text coinCount;
    
    void OnTriggerEnter2D(Collider2D other){
    	if(other.gameObject.name=="PlayerMB"){
    		switch(bonusName){
    			case "coin":
    				int coins=PlayerPrefs.GetInt("coins");
    				PlayerPrefs.SetInt("coins",coins+1);
    				coinCount.text=((coins+1).ToString())+"/7";
    				Destroy(gameObject);
    				break;
    			case "ship":
    				DiePanel.SetActive(true);
					Time.timeScale=0f;
					break;
				case "end":
					EndPanel.SetActive(true);
					Time.timeScale=0f;
					break;
    		}
    	}
    }
}
