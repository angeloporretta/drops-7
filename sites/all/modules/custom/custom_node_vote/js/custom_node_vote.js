jQuery( document ).ready(function() {
  //hide "Allow voting for this node if comments are closed"
  var form_item = jQuery("#edit-comment-2");
  if (document.getElementById("edit-comment-2") != null && !jQuery("#edit-comment-2").prop('checked')) {
    jQuery(".comment-like-setting")[0].style.display = "none";
  }
  jQuery("#edit-comment .form-radio").click(function(){
    if (jQuery(this)[0].id == 'edit-comment-2') {
      jQuery(".comment-like-setting")[0].style.display = "block";
    } else {
      jQuery(".comment-like-setting")[0].style.display = "none";
    }
  });
  //functionality for click on like
  jQuery('.comment-like-link').click(function(){
    var mySpan = document.createElement("span");
    mySpan.innerHTML = 0;
  	var notes = null;
  	var parent = this.parentNode.parentNode.parentNode
  	for (var i = 0; i < parent.childNodes.length; i++) {
      if (parent.childNodes[i].className == "like-count") {
        notes = parent.childNodes[i];
        var count = parseInt(notes.innerHTML);
        if ((jQuery(this)).hasClass('first')) {
          notes.innerHTML = count+1;
        } else {
          notes.innerHTML = count+1;
        }
      }        
	  }
    jQuery(this.parentNode).removeClass("comment-like").addClass("comment-like-hide");
    var menu = this.parentNode.parentNode;
    var unlike = menu.getElementsByClassName("comment-unlike-hide");
    jQuery(unlike[0]).removeClass("comment-unlike-hide").addClass("comment-unlike");
  	//this.parentNode.parentNode.parentNode.replaceChild();
  	// var mySpan = document.createElement("span");
   //  mySpan.className = mySpan.className + " comment-like-link";
  	// mySpan.innerHTML = '<a href="/comment/16/unlike/nojs" class="use-ajax comment-unlike-link ajax-processed">Unlike</a>';
  	// this.parentNode.replaceChild(mySpan , this);
  });

  //functionality for click on unlike
  jQuery('.comment-unlike-link').click(function(){
    var mySpan = document.createElement("span");
    mySpan.innerHTML = 0;
    var notes = null;
    var parent = this.parentNode.parentNode.parentNode
    for (var i = 0; i < parent.childNodes.length; i++) {
      if (parent.childNodes[i].className == "like-count") {
        notes = parent.childNodes[i];
        var count = parseInt(notes.innerHTML);
        notes.innerHTML = count-1;
      }        
    }
    jQuery(this.parentNode).removeClass("comment-unlike").addClass("comment-unlike-hide");
    var menu = this.parentNode.parentNode;
    var unlike = menu.getElementsByClassName("comment-like-hide");
    jQuery(unlike[0]).removeClass("comment-like-hide").addClass("comment-like");
    //this.parentNode.parentNode.parentNode.replaceChild();
    // var mySpan = document.createElement("span");
    // mySpan.innerHTML = "Unlike";
    // mySpan.className = mySpan.className + " comment-unlike-link"
    // this.parentNode.replaceChild(mySpan , this);
  });
});