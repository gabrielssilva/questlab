/**
 * http://stackoverflow.com/questions/1064089/inserting-a-text-where-cursor-is-using-javascript-jquery/1064139#1064139
 */
function getCaret(textareaId)
{
    var textarea = document.getElementById(textareaId);
    var strPos = 0;
    if(textarea.selectionStart || textarea.selectionStart == '0') {
        strPos = textarea.selectionStart
    }
    else if(document.selection)
    {
        textarea.focus();
        var range = document.selection.createRange();
        range.moveStart('character', -textarea.value.length);
        strPos = range.text.length;
    }
    else {
        strPos = -1;
    }

    return strPos;
}


function insertAtCaret(textareaId, caret, text)
{
    var textarea = document.getElementById(textareaId);
    var scrollPos = textarea.scrollTop;

    var front = (textarea.value).substring(0, caret);
    var back = (textarea.value).substring(caret, textarea.value.length);
    textarea.value = front + text + back;
    caret = caret + text.length;

    if(textarea.selectionStart || textarea.selectionStart == '0')
    {
        textarea.selectionStart = caret;
        textarea.selectionEnd = caret;
        textarea.focus();
    }
    else if(document.selection)
    {
        textarea.focus();
        var range = document.selection.createRange();
        range.moveStart('character', -textarea.value.length);
        range.moveStart('character', caret);
        range.moveEnd('character', 0);
        range.select();
    }
    textarea.scrollTop = scrollPos;
}




/**
 * Drag&Drop-functions
 */

function onDragStart(event)
{
    jQuery(event.currentTarget).addClass("drag");
    event.dataTransfer.setData("Text", event.target.id);
}

function onDragEnter(event)
{
    if(event.target.nodeName == "DIV" && !(event.target.parentNode.id == "dropZone" && event.target.hasChildNodes())) {
        jQuery(event.target).addClass('drop');
    }
}

function onDragOver(event)
{
    if(event.target.nodeName == "DIV" && !(event.target.parentNode.id == "dropZone" && event.target.hasChildNodes())) {
        event.preventDefault();
    }
}

function onDragLeave(event)
{
    jQuery(event.target).removeClass('drop');
}

function onDragEnd(event)
{
    jQuery(event.currentTarget).removeClass("drag");
}

function onDrop(event, setId)
{
    setId = (typeof setId == 'undefined') ? true : setId;
    jQuery(event.currentTarget).removeClass('drag');
    jQuery(event.target).removeClass('drop');
    event.preventDefault();

    var data = event.dataTransfer.getData("Text");
    var dataElement = $('#'+data);
    if(dataElement.parent() && $('#dnd_'+dataElement.parent().attr('id'))) {
        $('#dnd_'+dataElement.parent().attr('id')).attr('value', "null");
    }
    jQuery(event.target).append(dataElement);

    if(setId) {
        console.log(data);
        $('#dnd_' + jQuery(event.target).attr('id')).attr('value', data);
    }
}




/**
 * Notification functions.
 */

/**
 * Play notification, if audio-element is present.
 */
function notify()
{
    var notifySound = $("#notify-sound");
    if(notifySound.length > 0) {
        notifySound.get(0).volume = 0.5;
        notifySound.get(0).play();
    }
}




$(function() {
    // Play notification
    notify();
});
