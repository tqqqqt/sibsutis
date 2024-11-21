using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;
using UnityEngine.SceneManagement;

public class PlayerControler : MonoBehaviour
{
	private Rigidbody2D rbody;
	private CapsuleCollider2D coll;
	private InputSystem inputActions;
	
	public float moveSpeed=0f, jumpSpeed=0f;
	public float acceleration=0f, decceleration=0f, velPower=0f;
	[SerializeField] LayerMask groundLayers;
	public Animator animator;

	private void Awake(){
		rbody=GetComponent<Rigidbody2D>();
        coll=GetComponent<CapsuleCollider2D>();
        
        inputActions=new InputSystem();
        if(inputActions!=null){
	        inputActions.Land.Enable();
	        inputActions.Land.Jump.performed += Jump;
	        inputActions.Land.Movement.performed += MoveFun;
	    }
	}

    void Start()
    {
        rbody=GetComponent<Rigidbody2D>();
        coll=GetComponent<CapsuleCollider2D>();
    }

    private void Update()
    {
    	if(inputActions!=null && rbody!=null){
	        Vector2 inputVector=inputActions.Land.Movement.ReadValue<Vector2>();
	        rbody.velocity=new Vector2(moveSpeed*inputVector.x,rbody.velocity.y);
	        animator.SetFloat("Speed",0);
	        if(inputVector.x==1){
	        	SpriteRenderer spriteRen=GetComponent<SpriteRenderer>();
	        	spriteRen.flipX=false;
	        	animator.SetFloat("Speed",Mathf.Abs(moveSpeed));
	    	}
	        else if(inputVector.x==-1){
	        	SpriteRenderer spriteRen=GetComponent<SpriteRenderer>();
	        	spriteRen.flipX=true;
	        	animator.SetFloat("Speed",Mathf.Abs(moveSpeed));
	    	}
	    	if(IsGrounded()) animator.SetBool("IsJumping",false);
			else animator.SetBool("IsJumping",true);
	    }
    }
    
    public void MoveFun(InputAction.CallbackContext context){
    	if(inputActions!=null && rbody!=null){
	    	Vector2 inputVector=context.ReadValue<Vector2>();
	    	//rbody.velocity=new Vector2(moveSpeed*inputVector.x,rbody.velocity.y);
	    	float targetSpeed=inputVector.x*moveSpeed;
	    	float speedDif=targetSpeed-rbody.velocity.x;
	    	float accelRate=(Mathf.Abs(targetSpeed) > 0.01f) ? acceleration : decceleration;
	    	float movement=Mathf.Pow(Mathf.Abs(speedDif) * accelRate,velPower) * Mathf.Sign(speedDif);
	    	rbody.AddForce(movement*Vector2.right);
	    }
    }
	
	public void Jump(InputAction.CallbackContext context){
		if(IsGrounded() && rbody!=null) rbody.AddForce(Vector2.up * jumpSpeed,ForceMode2D.Impulse);
		// rbody.velocity=new Vector2(rbody.velocity.x,jumpSpeed);
	}
	
	bool IsGrounded(){
		if(rbody==null || coll==null) return false;
		return Physics2D.BoxCast(coll.bounds.center,coll.bounds.size,0f,Vector2.down,.1f,groundLayers);
	}
	
	void onEnable(){

    }
	
	void onDestroy(){
		inputActions.Land.Disable();
	}
}
