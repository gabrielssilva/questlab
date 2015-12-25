<?=$moodpic?>
<ul class="breadcrumbs">
    <li><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></li>
    <li><i class="fa fa-chevron-right fa-fw"></i><a href="<?=$linker->link(array('charactergroups','index',$seminary['url']))?>"><?=_('Character Groups')?></a></li>
    <li><i class="fa fa-chevron-right fa-fw"></i><a href="<?=$linker->link(array('charactergroups','groupsgroup',$seminary['url'],$groupsgroup['url']))?>"><?=$groupsgroup['name']?></a></li>
    <li><i class="fa fa-chevron-right fa-fw"></i><a href="<?=$linker->link(array('charactergroupsquests','quest',$seminary['url'],$groupsgroup['url'],$quest['url']))?>"><?=$quest['title']?></a></li>
</ul>

<?php if(count(array_intersect(array('admin', 'moderator'), \hhu\z\controllers\SeminaryController::$character['characterroles'])) > 0) : ?>
<nav class="admin">
    <li><a href="<?=$linker->link(array('edit',$seminary['url'],$groupsgroup['url'],$quest['url'],$station['url']),1)?>"><?=_('Edit')?></a></li>
    <li><a href="<?=$linker->link(array('delete',$seminary['url'],$groupsgroup['url'],$quest['url'],$station['url']),1)?>"><?=_('Delete')?></a></li>
    <li><a href="<?=$linker->link(array('manage',$seminary['url'],$groupsgroup['url'],$quest['url'],$station['url']),1)?>"><?=_('Manage')?></a></li>
</nav>
<?php endif ?>

<?php if(array_key_exists('picture', $station)) : ?>
<h1><?=$station['title']?></h1>
<?php endif ?>
<ul class="gdata cf">
    <?php if(!empty($station['longitude']) && !empty($station['latitude'])) : ?>
    <li>
        <span class="fwb"><?=sprintf(_('%1.6F°%s %1.6F°%s'), $station['latitude'], ($station['latitude']>0)?'N':'S', $station['longitude'], ($station['longitude']>0)?'E':'W')?></span>
    </li>
    <?php endif ?>
    <?php if(count(array_intersect(array('admin', 'moderator'), \hhu\z\controllers\SeminaryController::$character['characterroles'])) > 0) : ?>
    <li>
        <a href="<?=$linker->link(array('qrcodes','charactergroupsqueststation',$seminary['url'],$groupsgroup['url'],$quest['url'],$station['url'],'50'))?>">
            <i class="fa fa-qrcode"></i>
        </a>
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
            <?php if($group['solved'] !== false) : ?>
            <span class="xp">
                <i class="fa fa-check-square-o fa-fw"></i>
                <?=_(sprintf('solved at %s', $timeFormatter->format(new \DateTime($group['solved']))))?>
            </span>
            <?php endif ?>
        </li>
        <?php endforeach ?>
    </ol>
</section>
<?php endif ?>

<?php if(!is_null($task)) : ?>
<section class="task">
    <h1 id="task"><?=_('Task')?></h1>

    <?php if($solved): ?>
    <div class="text">
        <?=$t->t($station['righttext'])?>
    </div>
    <?php elseif($tried) : ?>
    <div class="text">
        <?=$t->t($station['wrongtext'])?>
    </div>
    <?php else : ?>
    <div class="text">
        <?=$t->t($station['task'])?>
        <?=$task?>
    </div>
    <?php endif ?>
</section>
<?php endif ?>
