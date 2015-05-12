jQuery(document).ready(function(){
  jQuery("#add-user-to-all-groups #edit-submit").click(function(e){
  	e.preventDefault();
  	var username = jQuery("#edit-user")[0]['value'];
  	jQuery.get('/user/autocomplete/' + username).then(function(response) {
  		var name = response[username];
  		var Alert = new CustomAlert();
  		Alert.render("This action for " + name + "'s user account cannot be undone. Are you sure you want to proceed?");
  	});
  });
});

function CustomAlert(){
    this.render = function(dialog){
        var winW = window.innerWidth;
        var winH = window.innerHeight;
        var dialogoverlay = document.getElementById('dialogoverlay');
        var dialogbox = document.getElementById('dialogbox');
        dialogoverlay.style.display = "block";
        dialogoverlay.style.height = winH+"px";
        dialogbox.style.left = (winW/2) - (550 * .5)+"px";
        dialogbox.style.top = "300px";
        dialogbox.style.display = "block";
        document.getElementById('dialogboxhead').innerHTML = "Warning!";
        document.getElementById('dialogboxbody').innerHTML = dialog;
        document.getElementById('dialogboxfoot').innerHTML = '<button onclick="Alert.ok()">OK</button><button onclick="' + "document.getElementById('dialogbox').style.display = 'none';document.getElementById('dialogoverlay').style.display = 'none';return false;" + '">Cancel</button>';
    }
	this.ok = function(){
		document.getElementById('dialogbox').style.display = "none";
		document.getElementById('dialogoverlay').style.display = "none";
	}
  this.cancel = function(){
    document.getElementById('dialogbox').style.display = "none";
    document.getElementById('dialogoverlay').style.display = "none";
    return false;
  }
}