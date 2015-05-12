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
