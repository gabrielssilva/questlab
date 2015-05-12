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
