//AABB/AABB Collisions
class Vector3;

bool AABBIntersection(const AABBVolume& volumeA, const Transform& worldTransformA,
	const AABBVolume& volumeB, const Transform& worldTransformB, CollisionInfo& collisionInfo) {


	bool intersected = AABBTest(boxAPos, boxBPos, boxASize, boxBSize);

	if (intersected) {
		static const Vector3 faces[6] =	//六个面的方向
		{
		Vector3(-1, 0, 0), Vector3(1, 0, 0),
			Vector3(0, -1, 0), Vector3(0, 1, 0),
			Vector3(0, 0, -1), Vector3(0, 0, 1),
		};

		Vector3 maxA = boxAPos + boxASize;
		Vector3 minA = boxAPos - boxASize;

		Vector3 maxB = boxBPos + boxBSize;
		Vector3 minB = boxBPos - boxBSize;

		float distances[6] =
		{
			(maxB.x - minA.x),// distance of box ’b’ to ’left ’ of ’a ’.
			(maxA.x - minB.x),// distance of box ’b’ to ’right ’ of ’a ’.
			(maxB.y - minA.y),// distance of box ’b’ to ’bottom ’ of ’a ’.
			(maxA.y - minB.y),// distance of box ’b’ to ’top ’ of ’a ’.
			(maxB.z - minA.z),// distance of box ’b’ to ’far ’ of ’a ’.
			(maxA.z - minB.z) // distance of box ’b’ to ’near ’ of ’a ’.
		};
		float penetration = FLT_MAX; //N
		Vector3 bestAxis;

		for (int i = 0; i < 6; i++)
		{
			if (distances[i] < penetration) {
				penetration = distances[i];
				bestAxis = faces[i];
			}
		}
		collisionInfo.AddContactPoint(Vector3(), Vector3(),
			bestAxis, penetration);
		return true;
	}
	return false;
}



bool AABBIntersectionTest(const Vector3& a_pos, const Vector3& b_pos, const Vector3& a_half_size, const Vector3& b_half_size, CollisionInfo& collisionInfo) {

	if (AABBIntersectionTest(a_pos, b_pos, a_half_size, b_half_size)) {
		static const Vector3 faces[6] =	//六个面的方向
		{
		Vector3(-1, 0, 0), Vector3(1, 0, 0),
			Vector3(0, -1, 0), Vector3(0, 1, 0),
			Vector3(0, 0, -1), Vector3(0, 0, 1),
		};

		Vector3 a_max = a_pos + a_half_size;
		Vector3 a_min = a_pos - a_half_size;

		Vector3 b_max = b_pos + b_half_size;
		Vector3 b_min = b_pos - b_half_size;

		float distances[6] =
		{
			(b_max.x - a_min.x),// distance of box ’b’ to ’left ’ of ’a ’.
			(a_max.x - b_min.x),// distance of box ’b’ to ’right ’ of ’a ’.
			(b_max.y - a_min.y),// distance of box ’b’ to ’bottom ’ of ’a ’.
			(a_max.y - b_min.y),// distance of box ’b’ to ’top ’ of ’a ’.
			(b_max.z - a_min.z),// distance of box ’b’ to ’far ’ of ’a ’.
			(a_max.z - b_min.z) // distance of box ’b’ to ’near ’ of ’a ’.
		};
		float penetration = FLT_MAX; //N
		Vector3 best_axis;

		for (int i = 0; i < 6; i++)
		{
			if (distances[i] < penetration) {	//最小必为负值，求深入深度为求最小值
				penetration = distances[i];
				best_axis = faces[i];
			}
		}
		collisionInfo.AddContactPoint({ 0, 0, 0 }, {0, 0, 0},
			bestAxis, penetration);
		return true;
	}

}

bool AABBIntersectionTest(const Vector3& a_pos, const Vector3& b_pos, const Vector3& a_half_size, const Vector3& b_half_size) {
	Vector3 delta = b_pos - a_pos;
	Vector3 totalSize = a_half_size + b_half_size;

	if (abs(delta.x) < totalSize.x &&   //当两个AABB的中心的距离小于两个的haflsize的和的时候则相交
		abs(delta.y) < totalSize.y &&
		abs(delta.z) < totalSize.z) {
		return true;

	}
	return false;
}