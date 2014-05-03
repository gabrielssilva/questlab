/*!
 * Piwik - Web Analytics
 *
 * JavaScript tracking client
 *
 * @link http://piwik.org
 * @source https://github.com/piwik/piwik/blob/master/js/piwik.js
 * @license http://piwik.org/free-software/bsd/ Simplified BSD (also in js/LICENSE.txt)
 */
if(typeof JSON2!=="object"){JSON2={}}(function(){function d(f){return f<10?"0"+f:f}function l(n,m){var f=Object.prototype.toString.apply(n);if(f==="[object Date]"){return isFinite(n.valueOf())?n.getUTCFullYear()+"-"+d(n.getUTCMonth()+1)+"-"+d(n.getUTCDate())+"T"+d(n.getUTCHours())+":"+d(n.getUTCMinutes())+":"+d(n.getUTCSeconds())+"Z":null}if(f==="[object String]"||f==="[object Number]"||f==="[object Boolean]"){return n.valueOf()}if(f!=="[object Array]"&&typeof n.toJSON==="function"){return n.toJSON(m)}return n}var c=new RegExp("[\u0000\u00ad\u0600-\u0604\u070f\u17b4\u17b5\u200c-\u200f\u2028-\u202f\u2060-\u206f\ufeff\ufff0-\uffff]","g"),e='\\\\\\"\x00-\x1f\x7f-\x9f\u00ad\u0600-\u0604\u070f\u17b4\u17b5\u200c-\u200f\u2028-\u202f\u2060-\u206f\ufeff\ufff0-\uffff]',i=new RegExp("["+e,"g"),j,b,k={"\b":"\\b","\t":"\\t","\n":"\\n","\f":"\\f","\r":"\\r",'"':'\\"',"\\":"\\\\"},h;
function a(f){i.lastIndex=0;return i.test(f)?'"'+f.replace(i,function(m){var n=k[m];return typeof n==="string"?n:"\\u"+("0000"+m.charCodeAt(0).toString(16)).slice(-4)})+'"':'"'+f+'"'}function g(s,p){var n,m,t,f,q=j,o,r=p[s];if(r&&typeof r==="object"){r=l(r,s)}if(typeof h==="function"){r=h.call(p,s,r)}switch(typeof r){case"string":return a(r);case"number":return isFinite(r)?String(r):"null";case"boolean":case"null":return String(r);case"object":if(!r){return"null"}j+=b;o=[];if(Object.prototype.toString.apply(r)==="[object Array]"){f=r.length;for(n=0;n<f;n+=1){o[n]=g(n,r)||"null"}t=o.length===0?"[]":j?"[\n"+j+o.join(",\n"+j)+"\n"+q+"]":"["+o.join(",")+"]";j=q;return t}if(h&&typeof h==="object"){f=h.length;for(n=0;n<f;n+=1){if(typeof h[n]==="string"){m=h[n];t=g(m,r);if(t){o.push(a(m)+(j?": ":":")+t)}}}}else{for(m in r){if(Object.prototype.hasOwnProperty.call(r,m)){t=g(m,r);if(t){o.push(a(m)+(j?": ":":")+t)}}}}t=o.length===0?"{}":j?"{\n"+j+o.join(",\n"+j)+"\n"+q+"}":"{"+o.join(",")+"}";j=q;
return t}}if(typeof JSON2.stringify!=="function"){JSON2.stringify=function(o,m,n){var f;j="";b="";if(typeof n==="number"){for(f=0;f<n;f+=1){b+=" "}}else{if(typeof n==="string"){b=n}}h=m;if(m&&typeof m!=="function"&&(typeof m!=="object"||typeof m.length!=="number")){throw new Error("JSON2.stringify")}return g("",{"":o})}}if(typeof JSON2.parse!=="function"){JSON2.parse=function(o,f){var n;function m(s,r){var q,p,t=s[r];if(t&&typeof t==="object"){for(q in t){if(Object.prototype.hasOwnProperty.call(t,q)){p=m(t,q);if(p!==undefined){t[q]=p}else{delete t[q]}}}}return f.call(s,r,t)}o=String(o);c.lastIndex=0;if(c.test(o)){o=o.replace(c,function(p){return"\\u"+("0000"+p.charCodeAt(0).toString(16)).slice(-4)})}if((new RegExp("^[\\],:{}\\s]*$")).test(o.replace(new RegExp('\\\\(?:["\\\\/bfnrt]|u[0-9a-fA-F]{4})',"g"),"@").replace(new RegExp('"[^"\\\\\n\r]*"|true|false|null|-?\\d+(?:\\.\\d*)?(?:[eE][+\\-]?\\d+)?',"g"),"]").replace(new RegExp("(?:^|:|,)(?:\\s*\\[)+","g"),""))){n=eval("("+o+")");
return typeof f==="function"?m({"":n},""):n}throw new SyntaxError("JSON2.parse")}}}());if(typeof _paq!=="object"){_paq=[]}if(typeof Piwik!=="object"){Piwik=(function(){var h,a={},q=document,d=navigator,D=screen,A=window,e=A.performance||A.mozPerformance||A.msPerformance||A.webkitPerformance,m=false,y=[],j=A.encodeURIComponent,z=A.decodeURIComponent,f=unescape,E,p,c;function s(P){var O=typeof P;return O!=="undefined"}function n(O){return typeof O==="function"}function C(O){return typeof O==="object"}function k(O){return typeof O==="string"||O instanceof String}function J(){var O,Q,P;for(O=0;O<arguments.length;O+=1){P=arguments[O];Q=P.shift();if(k(Q)){E[Q].apply(E,P)}else{Q.apply(E,P)}}}function M(R,Q,P,O){if(R.addEventListener){R.addEventListener(Q,P,O);return true}if(R.attachEvent){return R.attachEvent("on"+Q,P)}R["on"+Q]=P}function H(P,S){var O="",R,Q;for(R in a){if(Object.prototype.hasOwnProperty.call(a,R)){Q=a[R][P];if(n(Q)){O+=Q(S)}}}return O}function K(){var O;H("unload");if(h){do{O=new Date()
}while(O.getTimeAlias()<h)}}function I(){var O;if(!m){m=true;H("load");for(O=0;O<y.length;O++){y[O]()}}return true}function l(){var P;if(q.addEventListener){M(q,"DOMContentLoaded",function O(){q.removeEventListener("DOMContentLoaded",O,false);I()})}else{if(q.attachEvent){q.attachEvent("onreadystatechange",function O(){if(q.readyState==="complete"){q.detachEvent("onreadystatechange",O);I()}});if(q.documentElement.doScroll&&A===A.top){(function O(){if(!m){try{q.documentElement.doScroll("left")}catch(Q){setTimeout(O,0);return}I()}}())}}}if((new RegExp("WebKit")).test(d.userAgent)){P=setInterval(function(){if(m||/loaded|complete/.test(q.readyState)){clearInterval(P);I()}},10)}M(A,"load",I,false)}function g(Q,P){var O=q.createElement("script");O.type="text/javascript";O.src=Q;if(O.readyState){O.onreadystatechange=function(){var R=this.readyState;if(R==="loaded"||R==="complete"){O.onreadystatechange=null;P()}}}else{O.onload=P}q.getElementsByTagName("head")[0].appendChild(O)}function t(){var O="";
try{O=A.top.document.referrer}catch(Q){if(A.parent){try{O=A.parent.document.referrer}catch(P){O=""}}}if(O===""){O=q.referrer}return O}function i(O){var Q=new RegExp("^([a-z]+):"),P=Q.exec(O);return P?P[1]:null}function b(O){var Q=new RegExp("^(?:(?:https?|ftp):)/*(?:[^@]+@)?([^:/#]+)"),P=Q.exec(O);return P?P[1]:O}function B(Q,P){var O="[\\?&#]"+P+"=([^&#]*)";var S=new RegExp(O);var R=S.exec(Q);return R?z(R[1]):""}function o(O){return f(j(O))}function L(ae){var Q=function(aj,W){return(aj<<W)|(aj>>>(32-W))},af=function(al){var aj="",ak,W;for(ak=7;ak>=0;ak--){W=(al>>>(ak*4))&15;aj+=W.toString(16)}return aj},T,ah,ag,P=[],Y=1732584193,V=4023233417,U=2562383102,S=271733878,R=3285377520,ad,ac,ab,aa,Z,ai,O,X=[];ae=o(ae);O=ae.length;for(ah=0;ah<O-3;ah+=4){ag=ae.charCodeAt(ah)<<24|ae.charCodeAt(ah+1)<<16|ae.charCodeAt(ah+2)<<8|ae.charCodeAt(ah+3);X.push(ag)}switch(O&3){case 0:ah=2147483648;break;case 1:ah=ae.charCodeAt(O-1)<<24|8388608;break;case 2:ah=ae.charCodeAt(O-2)<<24|ae.charCodeAt(O-1)<<16|32768;
break;case 3:ah=ae.charCodeAt(O-3)<<24|ae.charCodeAt(O-2)<<16|ae.charCodeAt(O-1)<<8|128;break}X.push(ah);while((X.length&15)!==14){X.push(0)}X.push(O>>>29);X.push((O<<3)&4294967295);for(T=0;T<X.length;T+=16){for(ah=0;ah<16;ah++){P[ah]=X[T+ah]}for(ah=16;ah<=79;ah++){P[ah]=Q(P[ah-3]^P[ah-8]^P[ah-14]^P[ah-16],1)}ad=Y;ac=V;ab=U;aa=S;Z=R;for(ah=0;ah<=19;ah++){ai=(Q(ad,5)+((ac&ab)|(~ac&aa))+Z+P[ah]+1518500249)&4294967295;Z=aa;aa=ab;ab=Q(ac,30);ac=ad;ad=ai}for(ah=20;ah<=39;ah++){ai=(Q(ad,5)+(ac^ab^aa)+Z+P[ah]+1859775393)&4294967295;Z=aa;aa=ab;ab=Q(ac,30);ac=ad;ad=ai}for(ah=40;ah<=59;ah++){ai=(Q(ad,5)+((ac&ab)|(ac&aa)|(ab&aa))+Z+P[ah]+2400959708)&4294967295;Z=aa;aa=ab;ab=Q(ac,30);ac=ad;ad=ai}for(ah=60;ah<=79;ah++){ai=(Q(ad,5)+(ac^ab^aa)+Z+P[ah]+3395469782)&4294967295;Z=aa;aa=ab;ab=Q(ac,30);ac=ad;ad=ai}Y=(Y+ad)&4294967295;V=(V+ac)&4294967295;U=(U+ab)&4294967295;S=(S+aa)&4294967295;R=(R+Z)&4294967295}ai=af(Y)+af(V)+af(U)+af(S)+af(R);return ai.toLowerCase()}function G(Q,O,P){if(Q==="translate.googleusercontent.com"){if(P===""){P=O
}O=B(O,"u");Q=b(O)}else{if(Q==="cc.bingj.com"||Q==="webcache.googleusercontent.com"||Q.slice(0,5)==="74.6."){O=q.links[0].href;Q=b(O)}}return[Q,O,P]}function u(P){var O=P.length;if(P.charAt(--O)==="."){P=P.slice(0,O)}if(P.slice(0,2)==="*."){P=P.slice(1)}return P}function N(P){P=P&&P.text?P.text:P;if(!k(P)){var O=q.getElementsByTagName("title");if(O&&s(O[0])){P=O[0].text}}return P}function w(O,P){if(P){return P}if(O.slice(-9)==="piwik.php"){O=O.slice(0,O.length-9)}return O}function v(S){var O="Piwik_Overlay";var V=new RegExp("index\\.php\\?module=Overlay&action=startOverlaySession&idSite=([0-9]+)&period=([^&]+)&date=([^&]+)$");var Q=V.exec(q.referrer);if(Q){var R=Q[1];if(R!==String(S)){return false}var U=Q[2],P=Q[3];A.name=O+"###"+U+"###"+P}var T=A.name.split("###");return T.length===3&&T[0]===O}function F(P,U,R){var T=A.name.split("###"),S=T[1],O=T[2],Q=w(P,U);g(Q+"plugins/Overlay/client/client.js?v=1",function(){Piwik_Overlay_Client.initialize(Q,R,S,O)})}function x(am,aN){var U=G(q.domain,A.location.href,t()),a7=u(U[0]),bm=U[1],aU=U[2],bn=false,aS="GET",S=am||"",aj="",aP="",bc=aN||"",aE,au=q.title,aw="7z|aac|apk|ar[cj]|as[fx]|avi|azw3|bin|csv|deb|dmg|docx?|epub|exe|flv|gif|gz|gzip|hqx|jar|jpe?g|js|mobi|mp(2|3|4|e?g)|mov(ie)?|ms[ip]|od[bfgpst]|og[gv]|pdf|phps|png|pptx?|qtm?|ra[mr]?|rpm|sea|sit|tar|t?bz2?|tgz|torrent|txt|wav|wm[av]|wpd||xlsx?|xml|z|zip",aQ=[a7],X=[],aI=[],al=[],aO=500,Y,an,Z,ab,ay=["pk_campaign","piwik_campaign","utm_campaign","utm_source","utm_medium"],at=["pk_kwd","piwik_kwd","utm_term"],bk="_pk_",ae,bl,ac=false,bf,aA,aD,ai=63072000000,ak=1800000,aF=15768000000,aB=true,ap=0,W=false,aJ={},T={},bg=200,a0={},bd={},aX=false,aV=false,aT,aK,af,ax=L,aW,aC;
function a2(bw,bt,bs,bv,br,bu){if(ac){return}var bq;if(bs){bq=new Date();bq.setTime(bq.getTime()+bs)}q.cookie=bw+"="+j(bt)+(bs?";expires="+bq.toGMTString():"")+";path="+(bv||"/")+(br?";domain="+br:"")+(bu?";secure":"")}function ah(bs){if(ac){return 0}var bq=new RegExp("(^|;)[ ]*"+bs+"=([^;]*)"),br=bq.exec(q.cookie);return br?z(br[2]):0}function bh(bq){var br;if(Z){br=new RegExp("#.*");return bq.replace(br,"")}return bq}function a6(bs,bq){var bt=i(bq),br;if(bt){return bq}if(bq.slice(0,1)==="/"){return i(bs)+"://"+b(bs)+bq}bs=bh(bs);br=bs.indexOf("?");if(br>=0){bs=bs.slice(0,br)}br=bs.lastIndexOf("/");if(br!==bs.length-1){bs=bs.slice(0,br+1)}return bs+bq}function aR(bt){var br,bq,bs;for(br=0;br<aQ.length;br++){bq=u(aQ[br].toLowerCase());if(bt===bq){return true}if(bq.slice(0,1)==="."){if(bt===bq.slice(1)){return true}bs=bt.length-bq.length;if((bs>0)&&(bt.slice(bs)===bq)){return true}}}return false}function bp(bq){var br=new Image(1,1);br.onload=function(){p=0};br.src=S+(S.indexOf("?")<0?"?":"&")+bq
}function a3(bq){try{var bs=A.XMLHttpRequest?new A.XMLHttpRequest():A.ActiveXObject?new ActiveXObject("Microsoft.XMLHTTP"):null;bs.open("POST",S,true);bs.onreadystatechange=function(){if(this.readyState===4&&this.status!==200){bp(bq)}};bs.setRequestHeader("Content-Type","application/x-www-form-urlencoded; charset=UTF-8");bs.send(bq)}catch(br){bp(bq)}}function az(bs,br){var bq=new Date();if(!bf){if(aS==="POST"){a3(bs)}else{bp(bs)}h=bq.getTime()+br}}function a1(bq){return bk+bq+"."+bc+"."+aW}function V(){if(ac){return"0"}if(!s(d.cookieEnabled)){var bq=a1("testcookie");a2(bq,"1");return ah(bq)==="1"?"1":"0"}return d.cookieEnabled?"1":"0"}function aL(){aW=ax((ae||a7)+(bl||"/")).slice(0,4)}function ag(){var br=a1("cvar"),bq=ah(br);if(bq.length){bq=JSON2.parse(bq);if(C(bq)){return bq}}return{}}function R(){if(W===false){W=ag()}}function bb(){var bq=new Date();aT=bq.getTime()}function ad(bu,br,bq,bt,bs,bv){a2(a1("id"),bu+"."+br+"."+bq+"."+bt+"."+bs+"."+bv,ai,bl,ae)}function Q(){var br=new Date(),bq=Math.round(br.getTime()/1000),bt=ah(a1("id")),bs;
if(bt){bs=bt.split(".");bs.unshift("0")}else{if(!aC){aC=ax((d.userAgent||"")+(d.platform||"")+JSON2.stringify(bd)+br.getTime()+Math.random()).slice(0,16)}bs=["1",aC,bq,0,bq,"",""]}return bs}function O(){var bq=ah(a1("ref"));if(bq.length){try{bq=JSON2.parse(bq);if(C(bq)){return bq}}catch(br){}}return["","",0,""]}function P(){var bq=ac;ac=false;a2(a1("id"),"",-86400,bl,ae);a2(a1("ses"),"",-86400,bl,ae);a2(a1("cvar"),"",-86400,bl,ae);a2(a1("ref"),"",-86400,bl,ae);ac=bq}function ba(bu){if(!bu||!C(bu)){return}var bt=[];var bs;for(bs in bu){if(Object.prototype.hasOwnProperty.call(bu,bs)){bt.push(bs)}}var bv={};bt.sort();var bq=bt.length;var br;for(br=0;br<bq;br++){bv[bt[br]]=bu[bt[br]]}return bv}function av(bs,bQ,bR,bt){var bO,br=new Date(),bA=Math.round(br.getTime()/1000),bU,bP,bv,bG,bL,bz,bJ,bw,bN,bu=1024,bW,bD,bK=W,bB=a1("ses"),bC=a1("ref"),bX=a1("cvar"),bH=Q(),bF=ah(bB),bM=O(),bT=aE||bm,bx,bq;if(ac){P()}if(bf){return""}bU=bH[0];bP=bH[1];bG=bH[2];bv=bH[3];bL=bH[4];bz=bH[5];if(!s(bH[6])){bH[6]=""
}bJ=bH[6];if(!s(bt)){bt=""}var bE=q.characterSet||q.charset;if(!bE||bE.toLowerCase()==="utf-8"){bE=null}bx=bM[0];bq=bM[1];bw=bM[2];bN=bM[3];if(!bF){var bS=ak/1000;if(!bz||(bA-bz)>bS){bv++;bz=bL}if(!aD||!bx.length){for(bO in ay){if(Object.prototype.hasOwnProperty.call(ay,bO)){bx=B(bT,ay[bO]);if(bx.length){break}}}for(bO in at){if(Object.prototype.hasOwnProperty.call(at,bO)){bq=B(bT,at[bO]);if(bq.length){break}}}}bW=b(aU);bD=bN.length?b(bN):"";if(bW.length&&!aR(bW)&&(!aD||!bD.length||aR(bD))){bN=aU}if(bN.length||bx.length){bw=bA;bM=[bx,bq,bw,bh(bN.slice(0,bu))];a2(bC,JSON2.stringify(bM),aF,bl,ae)}}bs+="&idsite="+bc+"&rec=1&r="+String(Math.random()).slice(2,8)+"&h="+br.getHours()+"&m="+br.getMinutes()+"&s="+br.getSeconds()+"&url="+j(bh(bT))+(aU.length?"&urlref="+j(bh(aU)):"")+"&_id="+bP+"&_idts="+bG+"&_idvc="+bv+"&_idn="+bU+(bx.length?"&_rcn="+j(bx):"")+(bq.length?"&_rck="+j(bq):"")+"&_refts="+bw+"&_viewts="+bz+(String(bJ).length?"&_ects="+bJ:"")+(String(bN).length?"&_ref="+j(bh(bN.slice(0,bu))):"")+(bE?"&cs="+j(bE):"");
for(bO in bd){if(Object.prototype.hasOwnProperty.call(bd,bO)){bs+="&"+bO+"="+bd[bO]}}if(bQ){bs+="&data="+j(JSON2.stringify(bQ))}else{if(ab){bs+="&data="+j(JSON2.stringify(ab))}}function by(bY,bZ){var b0=JSON2.stringify(bY);if(b0.length>2){return"&"+bZ+"="+j(b0)}return""}var bV=ba(aJ);var bI=ba(T);bs+=by(bV,"cvar");bs+=by(bI,"e_cvar");if(W){bs+=by(W,"_cvar");for(bO in bK){if(Object.prototype.hasOwnProperty.call(bK,bO)){if(W[bO][0]===""||W[bO][1]===""){delete W[bO]}}}a2(bX,JSON2.stringify(W),ak,bl,ae)}if(aB){if(ap){bs+="&gt_ms="+ap}else{if(e&&e.timing&&e.timing.requestStart&&e.timing.responseEnd){bs+="&gt_ms="+(e.timing.responseEnd-e.timing.requestStart)}}}ad(bP,bG,bv,bA,bz,s(bt)&&String(bt).length?bt:bJ);a2(bB,"*",ak,bl,ae);bs+=H(bR);if(aP.length){bs+="&"+aP}return bs}function a5(bt,bs,bx,bu,bq,bA){var bv="idgoal=0",bw,br=new Date(),by=[],bz;if(String(bt).length){bv+="&ec_id="+j(bt);bw=Math.round(br.getTime()/1000)}bv+="&revenue="+bs;if(String(bx).length){bv+="&ec_st="+bx}if(String(bu).length){bv+="&ec_tx="+bu
}if(String(bq).length){bv+="&ec_sh="+bq}if(String(bA).length){bv+="&ec_dt="+bA}if(a0){for(bz in a0){if(Object.prototype.hasOwnProperty.call(a0,bz)){if(!s(a0[bz][1])){a0[bz][1]=""}if(!s(a0[bz][2])){a0[bz][2]=""}if(!s(a0[bz][3])||String(a0[bz][3]).length===0){a0[bz][3]=0}if(!s(a0[bz][4])||String(a0[bz][4]).length===0){a0[bz][4]=1}by.push(a0[bz])}}bv+="&ec_items="+j(JSON2.stringify(by))}bv=av(bv,ab,"ecommerce",bw);az(bv,aO)}function a4(bq,bu,bt,bs,br,bv){if(String(bq).length&&s(bu)){a5(bq,bu,bt,bs,br,bv)}}function bj(bq){if(s(bq)){a5("",bq,"","","","")}}function aH(bt,bu){var bq=new Date(),bs=av("action_name="+j(N(bt||au)),bu,"log");az(bs,aO);if(Y&&an&&!aV){aV=true;M(q,"click",bb);M(q,"mouseup",bb);M(q,"mousedown",bb);M(q,"mousemove",bb);M(q,"mousewheel",bb);M(A,"DOMMouseScroll",bb);M(A,"scroll",bb);M(q,"keypress",bb);M(q,"keydown",bb);M(q,"keyup",bb);M(A,"resize",bb);M(A,"focus",bb);M(A,"blur",bb);aT=bq.getTime();setTimeout(function br(){var bv;bq=new Date();if((aT+an)>bq.getTime()){if(Y<bq.getTime()){bv=av("ping=1",bu,"ping");
az(bv,aO)}setTimeout(br,an)}},an)}}function aa(bs,bu,bq,bt,bv){if(String(bs).length===0||String(bu).length===0){return false}var br=av("e_c="+j(bs)+"&e_a="+j(bu)+(s(bq)?"&e_n="+j(bq):"")+(s(bt)?"&e_v="+j(bt):""),bv,"event");az(br,aO)}function ar(bq,bt,br,bu){var bs=av("search="+j(bq)+(bt?"&search_cat="+j(bt):"")+(s(br)?"&search_count="+br:""),bu,"sitesearch");az(bs,aO)}function aM(bq,bt,bs){var br=av("idgoal="+bq+(bt?"&revenue="+bt:""),bs,"goal");az(br,aO)}function a9(br,bq,bt){var bs=av(bq+"="+j(bh(br)),bt,"link");az(bs,aO)}function be(br,bq){if(br!==""){return br+bq.charAt(0).toUpperCase()+bq.slice(1)}return bq}function aq(bv){var bu,bq,bt=["","webkit","ms","moz"],bs;if(!aA){for(bq=0;bq<bt.length;bq++){bs=bt[bq];if(Object.prototype.hasOwnProperty.call(q,be(bs,"hidden"))){if(q[be(bs,"visibilityState")]==="prerender"){bu=true}break}}}if(bu){M(q,bs+"visibilitychange",function br(){q.removeEventListener(bs+"visibilitychange",br,false);bv()});return}bv()}function ao(bs,br){var bt,bq="(^| )(piwik[_-]"+br;
if(bs){for(bt=0;bt<bs.length;bt++){bq+="|"+bs[bt]}}bq+=")( |$)";return new RegExp(bq)}function a8(bt,bq,bu){var bs=ao(aI,"download"),br=ao(al,"link"),bv=new RegExp("\\.("+aw+")([?&#]|$)","i");return br.test(bt)?"link":(bs.test(bt)||bv.test(bq)?"download":(bu?0:"link"))}function aZ(bv){var bt,br,bq;bt=bv.parentNode;while(bt!==null&&s(bt)){br=bv.tagName.toUpperCase();if(br==="A"||br==="AREA"){break}bv=bt;bt=bv.parentNode}if(s(bv.href)){var bw=bv.hostname||b(bv.href),bx=bw.toLowerCase(),bs=bv.href.replace(bw,bx),bu=new RegExp("^(javascript|vbscript|jscript|mocha|livescript|ecmascript|mailto):","i");if(!bu.test(bs)){bq=a8(bv.className,bs,aR(bx));if(bq){bs=f(bs);a9(bs,bq)}}}}function bo(bq){var br,bs;bq=bq||A.event;br=bq.which||bq.button;bs=bq.target||bq.srcElement;if(bq.type==="click"){if(bs){aZ(bs)}}else{if(bq.type==="mousedown"){if((br===1||br===2)&&bs){aK=br;af=bs}else{aK=af=null}}else{if(bq.type==="mouseup"){if(br===aK&&bs===af){aZ(bs)}aK=af=null}}}}function aY(br,bq){if(bq){M(br,"mouseup",bo,false);
M(br,"mousedown",bo,false)}else{M(br,"click",bo,false)}}function aG(br){if(!aX){aX=true;var bs,bq=ao(X,"ignore"),bt=q.links;if(bt){for(bs=0;bs<bt.length;bs++){if(!bq.test(bt[bs].className)){aY(bt[bs],br)}}}}}function bi(){var br,bs,bt={pdf:"application/pdf",qt:"video/quicktime",realp:"audio/x-pn-realaudio-plugin",wma:"application/x-mplayer2",dir:"application/x-director",fla:"application/x-shockwave-flash",java:"application/x-java-vm",gears:"application/x-googlegears",ag:"application/x-silverlight"},bq=(new RegExp("Mac OS X.*Safari/")).test(d.userAgent)?A.devicePixelRatio||1:1;if(!((new RegExp("MSIE")).test(d.userAgent))){if(d.mimeTypes&&d.mimeTypes.length){for(br in bt){if(Object.prototype.hasOwnProperty.call(bt,br)){bs=d.mimeTypes[bt[br]];bd[br]=(bs&&bs.enabledPlugin)?"1":"0"}}}if(typeof navigator.javaEnabled!=="unknown"&&s(d.javaEnabled)&&d.javaEnabled()){bd.java="1"}if(n(A.GearsFactory)){bd.gears="1"}bd.cookie=V()}bd.res=D.width*bq+"x"+D.height*bq}bi();aL();return{getVisitorId:function(){return(Q())[1]
},getVisitorInfo:function(){return Q()},getAttributionInfo:function(){return O()},getAttributionCampaignName:function(){return O()[0]},getAttributionCampaignKeyword:function(){return O()[1]},getAttributionReferrerTimestamp:function(){return O()[2]},getAttributionReferrerUrl:function(){return O()[3]},setTrackerUrl:function(bq){S=bq},setSiteId:function(bq){bc=bq},setCustomData:function(bq,br){if(C(bq)){ab=bq}else{if(!ab){ab=[]}ab[bq]=br}},appendToTrackingUrl:function(bq){aP=bq},getCustomData:function(){return ab},setCustomVariable:function(br,bq,bu,bs){var bt;if(!s(bs)){bs="visit"}if(!s(bq)){return}if(!s(bu)){bu=""}if(br>0){bq=!k(bq)?String(bq):bq;bu=!k(bu)?String(bu):bu;bt=[bq.slice(0,bg),bu.slice(0,bg)];if(bs==="visit"||bs===2){R();W[br]=bt}else{if(bs==="page"||bs===3){aJ[br]=bt}else{if(bs==="event"){T[br]=bt}}}}},getCustomVariable:function(br,bs){var bq;if(!s(bs)){bs="visit"}if(bs==="page"||bs===3){bq=aJ[br]}else{if(bs==="event"){bq=T[br]}else{if(bs==="visit"||bs===2){R();bq=W[br]}}}if(!s(bq)||(bq&&bq[0]==="")){return false
}return bq},deleteCustomVariable:function(bq,br){if(this.getCustomVariable(bq,br)){this.setCustomVariable(bq,"","",br)}},setLinkTrackingTimer:function(bq){aO=bq},setDownloadExtensions:function(bq){aw=bq},addDownloadExtensions:function(bq){aw+="|"+bq},setDomains:function(bq){aQ=k(bq)?[bq]:bq;aQ.push(a7)},setIgnoreClasses:function(bq){X=k(bq)?[bq]:bq},setRequestMethod:function(bq){aS=bq||"GET"},setReferrerUrl:function(bq){aU=bq},setCustomUrl:function(bq){aE=a6(bm,bq)},setDocumentTitle:function(bq){au=bq},setAPIUrl:function(bq){aj=bq},setDownloadClasses:function(bq){aI=k(bq)?[bq]:bq},setLinkClasses:function(bq){al=k(bq)?[bq]:bq},setCampaignNameKey:function(bq){ay=k(bq)?[bq]:bq},setCampaignKeywordKey:function(bq){at=k(bq)?[bq]:bq},discardHashTag:function(bq){Z=bq},setCookieNamePrefix:function(bq){bk=bq;W=ag()},setCookieDomain:function(bq){ae=u(bq);aL()},setCookiePath:function(bq){bl=bq;aL()},setVisitorCookieTimeout:function(bq){ai=bq*1000},setSessionCookieTimeout:function(bq){ak=bq*1000},setReferralCookieTimeout:function(bq){aF=bq*1000
},setConversionAttributionFirstReferrer:function(bq){aD=bq},disableCookies:function(){ac=true;bd.cookie="0"},deleteCookies:function(){P()},setDoNotTrack:function(br){var bq=d.doNotTrack||d.msDoNotTrack;bf=br&&(bq==="yes"||bq==="1");if(bf){this.disableCookies()}},addListener:function(br,bq){aY(br,bq)},enableLinkTracking:function(bq){if(m){aG(bq)}else{y.push(function(){aG(bq)})}},enableJSErrorTracking:function(){if(bn){return}bn=true;var bq=A.onerror;A.onerror=function(bv,bt,bs,bu,br){aq(function(){var bw="JavaScript Errors";var bx=bt+":"+bs;if(bu){bx+=":"+bu}aa(bw,bx,bv)});if(bq){return bq(bv,bt,bs,bu,br)}return false}},disablePerformanceTracking:function(){aB=false},setGenerationTimeMs:function(bq){ap=parseInt(bq,10)},setHeartBeatTimer:function(bs,br){var bq=new Date();Y=bq.getTime()+bs*1000;an=br*1000},killFrame:function(){if(A.location!==A.top.location){A.top.location=A.location}},redirectFile:function(bq){if(A.location.protocol==="file:"){A.location=bq}},setCountPreRendered:function(bq){aA=bq
},trackGoal:function(bq,bs,br){aq(function(){aM(bq,bs,br)})},trackLink:function(br,bq,bs){aq(function(){a9(br,bq,bs)})},trackPageView:function(bq,br){if(v(bc)){aq(function(){F(S,aj,bc)})}else{aq(function(){aH(bq,br)})}},trackEvent:function(br,bt,bq,bs){aq(function(){aa(br,bt,bq,bs)})},trackSiteSearch:function(bq,bs,br){aq(function(){ar(bq,bs,br)})},setEcommerceView:function(bt,bq,bs,br){if(!s(bs)||!bs.length){bs=""}else{if(bs instanceof Array){bs=JSON2.stringify(bs)}}aJ[5]=["_pkc",bs];if(s(br)&&String(br).length){aJ[2]=["_pkp",br]}if((!s(bt)||!bt.length)&&(!s(bq)||!bq.length)){return}if(s(bt)&&bt.length){aJ[3]=["_pks",bt]}if(!s(bq)||!bq.length){bq=""}aJ[4]=["_pkn",bq]},addEcommerceItem:function(bu,bq,bs,br,bt){if(bu.length){a0[bu]=[bu,bq,bs,br,bt]}},trackEcommerceOrder:function(bq,bu,bt,bs,br,bv){a4(bq,bu,bt,bs,br,bv)},trackEcommerceCartUpdate:function(bq){bj(bq)}}}function r(){return{push:J}}M(A,"beforeunload",K,false);l();Date.prototype.getTimeAlias=Date.prototype.getTime;E=new x();for(p=0;
p<_paq.length;p++){if(_paq[p][0]==="setTrackerUrl"||_paq[p][0]==="setAPIUrl"||_paq[p][0]==="setSiteId"){J(_paq[p]);delete _paq[p]}}for(p=0;p<_paq.length;p++){if(_paq[p]){J(_paq[p])}}_paq=new r();c={addPlugin:function(O,P){a[O]=P},getTracker:function(O,P){return new x(O,P)},getAsyncTracker:function(){return E}};if(typeof define==="function"&&define.amd){define("piwik",[],function(){return c})}return c}())}if(typeof piwik_log!=="function"){piwik_log=function(b,f,d,g){function a(h){try{return eval("piwik_"+h)}catch(i){}return}var c,e=Piwik.getTracker(d,f);e.setDocumentTitle(b);e.setCustomData(g);c=a("tracker_pause");if(c){e.setLinkTrackingTimer(c)}c=a("download_extensions");if(c){e.setDownloadExtensions(c)}c=a("hosts_alias");if(c){e.setDomains(c)}c=a("ignore_classes");if(c){e.setIgnoreClasses(c)}e.trackPageView();if(a("install_tracker")){piwik_track=function(i,k,j,h){e.setSiteId(k);e.setTrackerUrl(j);e.trackLink(i,h)};e.enableLinkTracking()}}};