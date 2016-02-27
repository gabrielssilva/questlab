<?=$moodpic?>
<ul class="breadcrumbs">
    <li><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></li>
    <li><i class="fa fa-chevron-right fa-fw"></i><a href="<?=$linker->link(array('charactergroups','index',$seminary['url']))?>"><?=_('Character Groups')?></a></li>
    <li><i class="fa fa-chevron-right fa-fw"></i><a href="<?=$linker->link(array('charactergroups','groupsgroup',$seminary['url'],$groupsgroup['url']))?>"><?=$groupsgroup['name']?></a></li>
</ul>

<?php if(count(array_intersect(array('admin', 'moderator'), \hhu\z\controllers\SeminaryController::$character['characterroles'])) > 0) : ?>
<nav class="admin">
    <li><a href="<?=$linker->link(array('edit',$seminary['url'],$groupsgroup['url'],$quest['url']),1)?>"><?=sprintf(_('Edit %s-Quest'), $groupsgroup['name'])?></a></li>
    <li><a href="<?=$linker->link(array('delete',$seminary['url'],$groupsgroup['url'],$quest['url']),1)?>"><?=sprintf(_('Delete %s-Quest'), $groupsgroup['name'])?></a></li>
    <li><a href="<?=$linker->link(array('manage',$seminary['url'],$groupsgroup['url'],$quest['url']),1)?>"><?=sprintf(_('Manage %s-Quest'), $groupsgroup['name'])?></a></li>
</nav>
<?php endif ?>

<div class="gbanner cf">
    <img src="<?=$linker->link(array('media','charactergroupsquest',$seminary['url'],$groupsgroup['url'],$quest['url']))?>" class="grpqimg" />
    <h1><?=$quest['title']?></h1>
</div>
<ul class="gdata cf">
    <li><span class="fwb"><?=sprintf(_('%d XPs'), $quest['xps'])?></span></li>
    <li><?php if($questgroup['entered']) : ?><a href="<?=$linker->link(array('questgroups','questgroup',$seminary['url'],$questgroup['url']))?>"><?=$questgroup['title']?></a><?php else : ?><?=$questgroup['title']?><?php endif ?></li>
</ul>

<?php if(count($uploads) > 0) : ?>
<section>
    <h1><i class="fa fa-picture-o fa-fw"></i><?=_('Media')?></h1>
    <ul class="gqgllry">
        <?php foreach($uploads as &$upload) : ?>
        <li>
            <a href="<?=$linker->link(array('uploads','seminary',$seminary['url'],$upload['upload']['url']))?>">
                <img src="<?=$linker->link(array('uploads','seminary',$seminary['url'],$upload['upload']['url'],'thumbnail'))?>" />
            </a>
        </li>
        <?php endforeach ?>
    </ul>
</section>
<?php endif ?>

<section>
    <h1><i class="fa fa-envelope fa-fw"></i><?=_('Description')?></h1>
    <div class="qtextbox">
        <p class="qtext"><?=$t->t($quest['description'])?></p>
    </div>
    <?php if(!empty($quest['rules'])) : ?>
    <h1><i class="fa fa-exclamation-triangle fa-fw"></i><?=_('Rules')?></h1>
    <div class="qtextbox">
        <p class="qtext"><?=$t->t($quest['rules'])?></p>
    </div>
    <?php endif ?>
</section>

<?php if(!empty($quest['won_text'])) : ?>
<section>   
    <h1><i class="fa fa-thumbs-up fa-fw"></i><?=_('Won Quest')?></h1>
    <div class="qtextbox">
        <p class="qtext"><?=$t->t($quest['won_text'])?></p>
    </div>
</section>
<?php endif ?>
<?php if(!empty($quest['lost_text'])) : ?>
<section>
    <h1><i class="fa fa-thumbs-down fa-fw"></i><?=_('Lost Quest')?></h1>
    <div class="qtextbox">
        <p class="qtext"><?=$t->t($quest['lost_text'])?></p>
    </div>
</section>
<?php endif ?>

<section>
    <h1 id="stations"><i class="fa fa-map-signs fa-fw"></i><?=_('Character Groups Quest Stations')?></h1>
    <?php if($stationsDiscovered || count(array_intersect(array('admin', 'moderator'), \hhu\z\controllers\SeminaryController::$character['characterroles'])) > 0) : ?>
    <div id="map" class="map"></div>
    <?php endif ?>

    <?php if(count(array_intersect(array('admin', 'moderator'), \hhu\z\controllers\SeminaryController::$character['characterroles'])) > 0) : ?>
    <nav class="admin">
        <ul>
            <li><a href="<?=$linker->link(array('charactergroupsqueststations','create',$seminary['url'],$groupsgroup['url'],$quest['url']))?>"><?=_('Create new station')?></a></li>
        </ul>
    </nav>
    <?php endif ?>
    <?php if(count($stationgroups) > 1) : ?>
    <form method="get" action="<?=$linker->link(null, 5, true, null, true, 'stations')?>">
        <label for="stationgroup"><?=sprintf(_('%s-Group to show'), $groupsgroup['name'])?>:</label>
        <select id="stationgroup" name="stationgroup" onchange="this.form.submit();">
            <?php if(count(array_intersect(array('admin', 'moderator'), \hhu\z\controllers\SeminaryController::$character['characterroles'])) > 0) : ?>
            <option><?=sprintf(_('Select %s-Group'), $groupsgroup['name'])?></option>
            <?php endif ?>
            <?php foreach($stationgroups as &$group) : ?>
            <option value="<?=$group['id']?>" <?php if($group['id'] == $stationgroup['id']) : ?>selected="selected"<?php endif ?>><?=$group['name']?></option>
            <?php endforeach ?>
        </select>
    </form>
    <?php endif ?>
    <ol class="grpqlist">
        <?php foreach($stations as &$station) : ?>
        <li>
            <span class="group">
                <?php if(!array_key_exists('entered', $station) || $station['entered']) : ?>
                <a href="<?=$linker->link(array('charactergroupsqueststations','station',$seminary['url'],$groupsgroup['url'],$quest['url'],$station['url']))?>"><?=$station['title']?></a>
                <?php else : ?>
                <?=_('Station not yet discovered')?>
                <?php endif ?>
            </span>
            <?php if(array_key_exists('entered', $station) && $station['entered']) : ?>
            <span class="xp">
                <?php if($station['tried']) : ?>
                <?php if($station['solved']) : ?>
                <i class="fa fa-check-circle fa-fw"></i>
                <?php else : ?>
                <i class="fa fa-times-circle fa-fw"></i>
                <?php endif ?>
                <?php else : ?>
                <i class="fa fa-globe fa-fw"></i>
                <?php endif ?>
            </span>
            <?php endif ?>
        </li>
        <?php endforeach ?>
    </ol>

    <ol class="grpqslist">
        <?php foreach($stations as &$station) : ?>
        <li>
            <?php if(array_key_exists('entered', $station) && $station['entered']) : ?>
            <a href="<?=$linker->link(array('charactergroupsqueststations','station',$seminary['url'],$groupsgroup['url'],$quest['url'],$station['url']))?>">
                <?php if($station['tried']) : ?>
                <?php if($station['solved']) : ?>
                <?php if(!is_null($station['stationpicture_id'])) : ?>
                <img title="<?=$station['title']?>" src="<?=$linker->link(array('media','charactergroupsqueststation',$seminary['url'],$groupsgroup['url'],$quest['url'],$station['url']))?>" />
                <?php else : ?>
                <i class="fa fa-circle"></i>
                <?php endif ?>
                <?php else : ?>
                <i class="fa fa-times-circle"></i>
                <?php endif ?>
                <?php else : ?>
                <img title="<?=$station['title']?>" src="<?=$linker->link(array('media','charactergroupsqueststation',$seminary['url'],$groupsgroup['url'],$quest['url'],$station['url']),0,true,array('stationgroup'=>$stationgroup['id']))?>" />
                <?php endif ?>
            </a>
            <?php else : ?>
            <div>
                <i class="fa fa-question-circle"></i>
            </div>
            <?php endif ?>
        </li>
        <?php endforeach ?>
    </ol>
</section>

<section>
    <h1><i class="fa fa-users fa-fw"></i><?=$groupsgroup['name']?></h1>
    <ol class="grpqlist">
        <?php foreach($groups as &$group) : ?>
        <li>
            <span class="date"><?=$dateFormatter->format(new \DateTime($group['created']))?></span>
            <span class="group"><a href="<?=$linker->link(array('charactergroups','group',$seminary['url'],$groupsgroup['url'],$group['url']))?>"><?=$group['name']?></a></span>
            <span class="xp">
<?php if(count(array_intersect(array('admin', 'moderator'), \hhu\z\controllers\SeminaryController::$character['characterroles'])) > 0) : ?>
                <?=sprintf(_('%d Stations'), count($group['stations']))?>,
<?php endif ?>
                <?=sprintf(_('%d XPs'), $group['xps'])?>
            </span>
        </li>
        <?php endforeach ?>
    </ol>
</section>

<script>
    var markersSource = new ol.source.Vector({
<?php if(!is_null($stationgroup)) : ?>
        url: '<?=$linker->link(array('charactergroupsqueststations','index',$seminary['url'],$groupsgroup['url'],$quest['url']), 0, true, array('stationgroup'=>$stationgroup['id']))?>',
<?php else : ?>
        url: '<?=$linker->link(array('charactergroupsqueststations','index',$seminary['url'],$groupsgroup['url'],$quest['url']))?>',
<?php endif ?>
        format: new ol.format.GeoJSON()
    });
    markersSource.on('change', function(e) {
        map.getView().fit(
            markersSource.getExtent(),
            map.getSize(), {
                padding: [10, 10, 10, 10]
            }
        );
    });
    var styleFunction = function(feature, resolution) {
        var styles = [];
        var geometry = feature.getGeometry();
        if(geometry instanceof ol.geom.Point) {
            var name = feature.get('name');
            if(name) {
                // Label styling
                styles.push(
                    new ol.style.Style({
                        text: new ol.style.Text({
                            text: name,
                            textBaseline: 'Bottom',
                            offsetY: 14,
                            scale: 1.2
                        })
                    })
                );
            }
            else {
                // Point styling
                styles.push(
                    new ol.style.Style({
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
                );
            }
        }
        else if(geometry instanceof ol.geom.LineString) {
            // Line styling
            styles.push(
                new ol.style.Style({
                    stroke: new ol.style.Stroke({
                        color: '#50A4AB',
                        width: 3
                    })
                })
            );
            // Add arrows
            geometry.forEachSegment(function(start, end) {
                var dx = end[0] - start[0];
                var dy = end[1] - start[1];
                var rotation = Math.atan2(dy, dx);
                var cx = (start[0] + end[0]) / 2;
                var cy = (start[1] + end[1]) / 2;
                styles.push(new ol.style.Style({
                    geometry: new ol.geom.Point([cx, cy]),
                    text: new ol.style.Text({
                        text: '\uf178',
                        font: 'normal 28px FontAwesome',
                        fill: new ol.style.Fill({
                            color: '#0F373C'
                        }),
                        rotation: -rotation
                    })
                }));
            });
        }

        return styles;
    };

    var map = new ol.Map({
        layers: [
            new ol.layer.Tile({
                source: new ol.source.OSM()
            }),
            new ol.layer.Vector({
                source: markersSource,
                style: styleFunction
            })
        ],
        target: 'map',
        view: new ol.View({
            center: [0, 0],
            zoom: 19,
            maxZoom: 19
        })
    });
</script>
