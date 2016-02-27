<?=$moodpic?>
<ul class="breadcrumbs">
    <li><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></li>
    <li><i class="fa fa-chevron-right fa-fw"></i><a href="<?=$linker->link(array('charactergroups','index',$seminary['url']))?>"><?=_('Character Groups')?></a></li>
    <li><i class="fa fa-chevron-right fa-fw"></i><a href="<?=$linker->link(array('charactergroups','groupsgroup',$seminary['url'],$groupsgroup['url']))?>"><?=$groupsgroup['name']?></a></li>
    <li><i class="fa fa-chevron-right fa-fw"></i><a href="<?=$linker->link(array('charactergroupsquests','quest',$seminary['url'],$groupsgroup['url'],$quest['url']))?>"><?=$quest['title']?></a></li>
</ul>

<div class="grpqsicon">
<?php if($entered) : ?>
<?php if($tried) : ?>
<?php if($solved) : ?>
<?php if($station['stationpicture_id']) : ?>
    <img title="<?=$station['title']?>" src="<?=$linker->link(array('media','charactergroupsqueststation',$seminary['url'],$groupsgroup['url'],$quest['url'],$station['url']))?>" />
<?php else : ?>
    <i class="fa fa-circle"></i>
<?php endif ?>
<?php else : ?>
    <i class="fa fa-times-circle"></i>
<?php endif ?>
<?php else : ?>
<?php if(!is_null($stationgroup)) : ?>
    <img title="<?=$station['title']?>" src="<?=$linker->link(array('media','charactergroupsqueststation',$seminary['url'],$groupsgroup['url'],$quest['url'],$station['url']),0,true,array('stationgroup'=>$stationgroup['id']))?>" />
<?php else : ?>
    <img title="<?=$station['title']?>" src="<?=$linker->link(array('media','charactergroupsqueststation',$seminary['url'],$groupsgroup['url'],$quest['url'],$station['url']),0,true)?>" />
<?php endif ?>
<?php endif ?>
<?php else : ?>
    <i class="fa fa-question-circle"></i>
<?php endif ?>
</div>

<h1><?=$station['title']?></h1>
<?php if(count(array_intersect(array('admin', 'moderator'), \hhu\z\controllers\SeminaryController::$character['characterroles'])) > 0) : ?>
<nav class="admin">
    <li><a href="<?=$linker->link(array('edit',$seminary['url'],$groupsgroup['url'],$quest['url'],$station['url']),1)?>"><?=_('edit')?></a></li>
    <li><a href="<?=$linker->link(array('delete',$seminary['url'],$groupsgroup['url'],$quest['url'],$station['url']),1)?>"><?=_('delete')?></a></li>
</nav>
<?php endif ?>

<ul class="gdata cf">
    <?php if(count(array_intersect(array('admin', 'moderator'), \hhu\z\controllers\SeminaryController::$character['characterroles'])) > 0) : ?>
    <li>
        <a href="<?=$linker->link(array('qrcodes','charactergroupsqueststation',$seminary['url'],$groupsgroup['url'],$quest['url'],$station['url'],'50'))?>">
            <i class="fa fa-qrcode"></i>
        </a>
    </li>
    <li>
        <?php if(count($stationgroups) > 1) : ?>
        <form method="get">
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
    </li>
    <?php endif ?>
<?php if($entered) : ?>
    <li>
<?php if($tried) : ?>
<?php if($solved) : ?>
        <i class="fa fa-check-circle fa-fw"></i>
        <?=$dateFormatter->format(new \DateTime($solved))?>
        <?=$timeFormatter->format(new \DateTime($solved))?>
<?php else : ?>
        <i class="fa fa-times-circle fa-fw"></i>
        <?=$dateFormatter->format(new \DateTime($tried))?>
        <?=$timeFormatter->format(new \DateTime($tried))?>
<?php endif ?>
<?php else : ?>
        <i class="fa fa-globe fa-fw"></i>
        <?=$dateFormatter->format(new \DateTime($entered))?>
        <?=$timeFormatter->format(new \DateTime($entered))?>
<?php endif ?>
    </li>
<?php endif ?>
</ul>

<?php if(!empty($station['longitude']) && !empty($station['latitude'])) : ?>
<section>
    <div id="map" class="map"></div>
    <script type="text/javascript">
        var center = ol.proj.transform([<?=$station['longitude']?>, <?=$station['latitude']?>], 'EPSG:4326', 'EPSG:3857');

        var markersSource = new ol.source.Vector();
        markersSource.addFeature(
            new ol.Feature({
                geometry: new ol.geom.Point(
                    ol.proj.transform([<?=$station['longitude']?>, <?=$station['latitude']?>], 'EPSG:4326', 'EPSG:3857')
                ),
                name: '<?=$station['title']?>'
            })
        );
        var markersStyle = new ol.style.Style({
            text: new ol.style.Text({
                //text: '\uf041',
                text: '\uf276',
                font: 'normal 28px FontAwesome',
                textBaseline: 'Bottom',
                fill: new ol.style.Fill({
                    color: '#0F373C'
                })
            })
        });
        var markersLayer = new ol.layer.Vector({
            source: markersSource,
            style: markersStyle
        });

        var map = new ol.Map({
            layers: [
                new ol.layer.Tile({
                    source: new ol.source.OSM()
                }),
                markersLayer
            ],
            controls: ol.control.defaults(),
            target: 'map',
            view: new ol.View({
                center: center,
                zoom: 18,
                maxZoom: 19
            })
        });
    </script>
</section>
<?php endif ?>

<?php if(!empty($groups)) : ?>
<section>
    <h1><?=_('Character Groups')?></h1>
    <ol class="grpqlist">
        <?php foreach($groups as &$group) : ?>
        <li>
            <span class="date">
                <?=$dateFormatter->format(new \DateTime($group['created']))?>
                <?=$timeFormatter->format(new \DateTime($group['created']))?>
            </span>
            <span class="group"><a href="<?=$linker->link(array('charactergroups','group',$seminary['url'],$groupsgroup['url'],$group['url']))?>"><?=$group['name']?></a></span>
            <span class="xp">
                <?php if($group['tried']) : ?>
                <?php if($group['solved']) : ?>
                <?=sprintf(_('solved at %s'), $timeFormatter->format(new \DateTime($group['solved'])))?>
                <i class="fa fa-check-circle fa-fw"></i>
                <?php else : ?>
                <?=sprintf(_('failed at %s'), $timeFormatter->format(new \DateTime($group['solved'])))?>
                <i class="fa fa-times-circle fa-fw"></i>
                <?php endif ?>
                <?php else : ?>
                <i class="fa fa-globe fa-fw"></i>
                <?php endif ?>
            </span>
        </li>
        <?php endforeach ?>
    </ol>
</section>
<?php endif ?>

<?php if(!empty($station['prolog'])) : ?>
<section>
    <div class="qtextbox">
        <p class="qtext cf">
            <?=str_replace('<p>', '', str_replace('</p>', '', $t->t($station['prolog'])))?>
        </p>
    </div>
</section>
<?php endif ?>

<section class="task">
<?php if(!is_null($task)) : ?>
    <h1 id="task"><?=_('Task')?></h1>

    <?php if($tried) : ?>
    <?php if($solved): ?>
    <div class="text">
        <?php if(array_key_exists('rightimage', $station)) : ?>
        <a href="<?=$linker->link(array('media','seminary',$seminary['url'],$station['rightimage']['url']))?>">
            <img src="<?=$linker->link(array('media','seminary',$seminary['url'],$station['rightimage']['url'],'charactergroupsqueststation'))?>" />
        </a><br />
        <?php endif ?>
        <?php if(array_key_exists('rightav', $station)) : ?>
            <?php if(strpos($station['rightav']['mimetype'], 'audio') !== false) : ?>
            <audio controls="controls" autoplay="autoplay" preload="metadata" src="<?=$linker->link(array('media','seminary',$seminary['url'],$station['rightav']['url']))?>"></audio>
            <?php else : ?>
            <video controls="controls" autoplay="autoplay" preload="metadata" src="<?=$linker->link(array('media','seminary',$seminary['url'],$station['rightav']['url']))?>"></video>
            <?php endif ?>
        <?php endif ?>
        <?=$t->t($station['righttext'])?>
    </div>
    <?php else : ?>
    <div class="text">
        <?php if(array_key_exists('wrongimage', $station)) : ?>
        <a href="<?=$linker->link(array('media','seminary',$seminary['url'],$station['wrongimage']['url']))?>">
            <img src="<?=$linker->link(array('media','seminary',$seminary['url'],$station['wrongimage']['url'],'charactergroupsqueststation'))?>" />
        </a><br />
        <?php endif ?>
        <?php if(array_key_exists('wrongav', $station)) : ?>
            <?php if(strpos($station['wrongav']['mimetype'], 'audio') !== false) : ?>
            <audio controls="controls" autoplay="autoplay" preload="metadata" src="<?=$linker->link(array('media','seminary',$seminary['url'],$station['wrongav']['url']))?>"></audio>
            <?php else : ?>
            <video controls="controls" autoplay="autoplay" preload="metadata" src="<?=$linker->link(array('media','seminary',$seminary['url'],$station['wrongav']['url']))?>"></video>
            <?php endif ?>
        <?php endif ?>
        <?=$t->t($station['wrongtext'])?>
    </div>
    <?php endif ?>
    <p>
        <a class="cta orange" href="<?=$linker->link(array('charactergroupsquests','quest',$seminary['url'],$groupsgroup['url'],$quest['url']))?>"><?=_('Back to overview')?></a>
    </p>
    <?php else : ?>
    <div>
        <?=$t->t($station['task'])?>
        <?=$task?>
    </div>
    <?php endif ?>
<?php else : ?>
    <p>
        <a class="cta orange" href="<?=$linker->link(array('charactergroupsquests','quest',$seminary['url'],$groupsgroup['url'],$quest['url']))?>"><?=_('Back to overview')?></a>
    </p>
<?php endif ?>
</section>
