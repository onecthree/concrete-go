
<style>#el{display: none;}</style><script>function z(x){return document.getElementById(x);}window.onload=function(){let b=z("el").innerHTML;let x=b.match(/(?<=\<b\>)\/(.*?)(?=\<\/b\>)|(?<=line <b>)(.*?)(?=\<\/b\>)/g);z("fc").innerHTML=x[0];z("lc").innerHTML=x[1];}</script><b>Fatal error:</b> FusionEngine: {"/route"} route already declared {main-0} throw in <b id="fc"></b> on line <b id="lc"></b><br /><div id="el">
<br /><b>Fatal error</b>:   in <b>/var/www/framework/routes/web.php</b> on line <b>12</b><br />
