using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class SceneScript : MonoBehaviour
{
    [SerializeField] private GameObject PausePanel;
    
    public void PauseButtonPressed(){
		PausePanel.SetActive(true);
		Time.timeScale=0f;
	}
	
	public void ContinueButtonPressed(){
		PausePanel.SetActive(false);
		Time.timeScale=1f;
	}
	
	public void RestartButtonPressed(){
		SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex);
		Time.timeScale=1f;
		PlayerPrefs.SetInt("coins",0);
	}
	
	public void ChangeScrene(int needIndex){
		SceneManager.LoadScene(needIndex);
		Time.timeScale=1f;
		PlayerPrefs.SetInt("coins",0);
	}
}
