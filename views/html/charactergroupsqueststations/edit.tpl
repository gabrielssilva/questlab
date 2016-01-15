<?=$moodpic?>
<ul class="breadcrumbs">
    <li><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></li>
    <li><i class="fa fa-chevron-right fa-fw"></i><a href="<?=$linker->link(array('charactergroups','index',$seminary['url']))?>"><?=_('Character Groups')?></a></li>
    <li><i class="fa fa-chevron-right fa-fw"></i><a href="<?=$linker->link(array('charactergroups','groupsgroup',$seminary['url'],$groupsgroup['url']))?>"><?=$groupsgroup['name']?></a></li>
    <li><i class="fa fa-chevron-right fa-fw"></i><a href="<?=$linker->link(array('charactergroupsquests','quest',$seminary['url'],$groupsgroup['url'],$quest['url']))?>"><?=$quest['title']?></a></li>
</ul>

<h1><?=_('Edit Station')?></h1>
<?php if($validation !== true && !empty($validation)) : ?>
<ul class="validation">
    <?php foreach($validation as $field => &$settings) : ?>
    <li>
        <ul>
            <?php foreach($settings as $setting => $value) : ?>
            <li>
                <?php switch($field) {
                    case 'icon':
                        switch($setting) {
                            case 'error': printf(_('Error during icon upload: %s'), $value);
                            break;
                            case 'mimetype': printf(_('Icon has wrong type “%s”'), $value);
                            break;
                            case 'size': echo _('Icon exceeds size maximum');
                            break;
                            default: echo _('Icon invalid');
                        }
                    break;
                    case 'title':
                        switch($setting) {
                            case 'minlength': printf(_('Title is too short (min. %d chars)'), $value);
                            break;
                            case 'maxlength': printf(_('Title is too long (max. %d chars)'), $value);
                            break;
                            case 'regex': echo _('Title contains illegal characters');
                            break;
                            case 'exist': echo _('Title already exists');
                            break;
                            default: echo _('Title invalid');
                        }
                    break;
                } ?>
            </li>
            <?php endforeach ?>
        </ul>
    </li>
    <?php endforeach ?>
</ul>
<?php endif ?>
<form method="post" action="" class="logreg" enctype="multipart/form-data">
    <fieldset>
        <legend><?=_('Icon')?></legend>
        <input type="file" name="icon" />
        <p><?=_('Allowed file types')?>:</p>
        <ul>
            <?php foreach($mimetypes as &$mimetype) : ?>
            <li><?=sprintf(_('%s-files'), strtoupper(explode('/',$mimetype['mimetype'])[1]))?> <?php if($mimetype['size'] > 0) : ?>(<?=_('max.')?> <?=round($mimetype['size']/(1024*1024),2)?> MiB)<?php endif ?></li>
            <?php endforeach ?>
        </ul>
    </fieldset>
    <fieldset>
        <legend><?=_('Location')?></legend>
        <div id="map" class="map"></div>
        <input id="longitude" name="longitude" type="hidden" value="<?=$longitude?>" />
        <input id="latitude" name="latitude" type="hidden" value="<?=$latitude?>" />
    </fieldset>
    <fieldset>
        <label for="stationtype"><?=('Stationtype')?>:</label>
        <select id="stationtype" name="stationtype">
            <?php foreach($stationtypes as &$stationtype) : ?>
            <option value="<?=$stationtype['url']?>" <?php if($stationtype['selected']) : ?>selected="selected"<?php endif ?>>
                <?php switch($stationtype['classname']) {
                    case null: echo _('Stationttype Empty');
                    break;
                    case 'multiplechoice': echo _('Stationtype multiplechoice');
                    break;
                    case 'keyword': echo _('Stationtype keyword');
                    break;
                } ?>
            </option>
            <?php endforeach ?>
        </select>
    </fieldset>
    <fieldset>
        <label for="title"><?=_('Title')?>:</label>
        <input type="text" id="title" name="title" placeholder="<?=_('Title')?>" title="<?=_('Title')?>" maxlength="<?=$validationSettings['title']['maxlength']?>" value="<?=$title?>" <?=($validation !== true && array_key_exists('title', $validation)) ? 'class="invalid"' : null?> />
        <label for="prolog"><?=_('Prolog')?>:</label><br />
        <textarea id="prolog" name="prolog" placeholder="<?=_('Prolog')?>" style="width:100%; height:10em;"><?=$prolog?></textarea><br />
        <label for="task"><?=_('Task')?>:</label><br />
        <textarea id="task" name="task" placeholder="<?=_('Task')?>" style="width:100%; height:10em;"><?=$task?></textarea><br />
        <label for="rightText"><?=('Right text')?>:</label><br />
        <textarea id="rightText" name="rightText" placeholder="<?=_('Right text')?>" style="width:100%; height:10em;"><?=$righttext?></textarea><br />
        <label for="wrongText"><?=_('Wrong text')?>:</label><br />
        <textarea id="wrongText" name="wrongText" placeholder="<?=_('Wrong text')?>" style="width:100%; height:10em;"><?=$wrongtext?></textarea><br />
    </fieldset>
    <?php if(!is_null($stationtype['classname'])) : ?>
    <input type="submit" name="edit-task" value="<?=_('edit task')?>" />
    <?php endif ?>
    <input type="submit" name="edit" value="<?=_('save')?>" />
</form>
<script>
    $(function() {
        $("#prolog").markItUp(mySettings);
        $("#task").markItUp(mySettings);
        $("#rightText").markItUp(mySettings);
        $("#wrongText").markItUp(mySettings);
    });

    var drawSource = new ol.source.Vector({
        wrapX: false
    });
    var drawLayer = new ol.layer.Vector({
        source: drawSource,
        style: new ol.style.Style({
            text: new ol.style.Text({
                //text: '\uf041',
                text: '\uf276',
                font: 'normal 28px FontAwesome',
                textBaseline: 'Bottom',
                fill: new ol.style.Fill({
                    color: '#0F373C'
                })
            })
        })
    });
    var map = new ol.Map({
        layers: [
            new ol.layer.Tile({
                source: new ol.source.OSM()
            }),
            drawLayer
        ],
        controls: ol.control.defaults(),
        target: 'map',
        view: new ol.View({
            center: [0, 0],
            zoom: 0,
            maxZoom: 19
        })
    });
    var draw = new ol.interaction.Draw({
        source: drawSource,
        type: 'Point',
        maxPoints: 1,
    });
    map.addInteraction(draw);

    // Add existing point
    var longitude = $('#longitude').val();
    var latitude = $('#latitude').val();
    if(longitude && latitude) {
        drawSource.addFeature(
            new ol.Feature({
                geometry: new ol.geom.Point(
                    ol.proj.transform([longitude, latitude], 'EPSG:4326', 'EPSG:3857')
                )
            })
        );
    }

    // Wire events
    drawSource.on('addfeature', function(event) {
        var coordinates = event.feature.getGeometry().getCoordinates();
        coordinates = ol.proj.transform(coordinates, 'EPSG:3857', 'EPSG:4326');
        $('#longitude').val(coordinates[0]);
        $('#latitude').val(coordinates[1]);
    });
    draw.on('drawstart', function() {
        drawSource.clear();
    });
</script>
