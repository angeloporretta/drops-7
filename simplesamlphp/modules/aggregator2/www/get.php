<?php

if (!isset($_REQUEST['id'])) {
	throw new SimpleSAML_Error_BadRequest('Missing required id-parameter.');
}
$id = (string)$_REQUEST['id'];

$aggregator = sspmod_aggregator2_Aggregator::getAggregator($id);
$xml = $aggregator->getMetadata();

header('Content-Type: application/samlmetadata+xml');
header('Content-Length: ' . strlen($xml));

/*
 * At this point, if the ID was forged, getMetadata() would
 * have failed to find a valid metadata set, so we can trust it.
 */
header('Content-Disposition: filename='.$id.'.xml');

echo($xml);
